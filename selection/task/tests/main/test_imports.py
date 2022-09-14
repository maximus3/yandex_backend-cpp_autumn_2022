import pytest

pytestmark = pytest.mark.asyncio


async def test_imports_post_validation_error(client):
    response = await client.post('/imports')
    assert response.status_code == 400, response.json()


async def test_imports_post_validation_error_with_json(client):
    response = await client.post('/imports', json={'aaa': 'bbb'})
    assert response.status_code == 400, response.json()


async def check_import_ok(web_client, batches):
    for batch in batches:
        response = await web_client.post('/imports', json=batch)
        assert response.status_code == 200, response.json()
        for item in batch['items']:
            response = await web_client.get(f'/nodes/{item["id"]}')
            assert response.status_code == 200, response.json()
            assert batch['updateDate'] == response.json()['date']


async def test_imports_post_ok(client, import_batches_data):
    await check_import_ok(client, import_batches_data)


async def test_imports_post_ok_if_exists(
        prepare_db, client, import_batches_data
):
    await check_import_ok(client, import_batches_data)


async def test_imports_post_not_iso_8601_text(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FOLDER',
                    'id': 'id',
                }
            ],
            'updateDate': 'aaa',
        },
    )
    assert response.status_code == 400, response.json()


async def test_imports_post_not_iso_8601(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FOLDER',
                    'id': 'id',
                }
            ],
            'updateDate': '2022-02-32T12:00:00',
        },
    )
    assert response.status_code == 400, response.json()


async def test_imports_post_not_iso_8601_with_dot(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FOLDER',
                    'id': 'id',
                }
            ],
            'updateDate': '2022-02-32T12:00:00.000',
        },
    )
    assert response.status_code == 400, response.json()


async def test_imports_post_iso_8601_ok(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FOLDER',
                    'id': 'id',
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 200, response.json()


async def test_imports_post_file_without_size(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FILE',
                    'url': '/file/1',
                    'id': 'id',
                    'size': 100,
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 400, response.json()


async def test_imports_post_folder_with_size(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FOLDER',
                    'id': 'id',
                    'size': 100,
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 400, response.json()


async def test_imports_post_folder_with_size_str(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FOLDER',
                    'id': 'id',
                    'size': '100',
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 400, response.json()


async def test_imports_post_file_size_neg(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FILE',
                    'url': '/file/1',
                    'id': 'id',
                    'size': -100,
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 400, response.json()


async def test_imports_post_file_size_zero_not_ok(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FILE',
                    'url': '/file/1',
                    'id': 'id',
                    'size': 0,
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 400, response.json()


async def test_imports_post_file_ok(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FILE',
                    'url': '/file/1',
                    'id': 'id',
                    'size': 100,
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 200, response.json()


async def test_imports_post_folder_ok(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FOLDER',
                    'id': 'id',
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 200, response.json()


async def test_imports_post_double_id(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FOLDER',
                    'id': 'id',
                },
                {
                    'type': 'FOLDER',
                    'id': 'id',
                },
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 400, response.json()


async def test_imports_post_double_id_diff(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FOLDER',
                    'id': 'id',
                },
                {
                    'type': 'FILE',
                    'url': '/file/1',
                    'id': 'id',
                    'size': 100,
                },
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 400, response.json()


async def test_imports_post_item_type_mismatch_cat_to_file(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FOLDER',
                    'id': 'id',
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 200, response.json()

    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FILE',
                    'url': '/file/1',
                    'id': 'id',
                    'size': 100,
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 400, response.json()


async def test_imports_post_item_type_mismatch_file_to_cat(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FILE',
                    'url': '/file/1',
                    'id': 'id',
                    'size': 100,
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 200, response.json()

    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FOLDER',
                    'id': 'id',
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 400, response.json()


async def test_imports_post_item_type_no_mismatch(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FILE',
                    'url': '/file/1',
                    'id': 'id',
                    'size': 100,
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 200, response.json()

    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FILE',
                    'url': '/file/2',
                    'id': 'id',
                    'size': 150,
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 200, response.json()


async def test_imports_post_parent_no_folder(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FILE',
                    'url': '/file/1',
                    'id': 'id1',
                    'size': 100,
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 200, response.json()

    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FILE',
                    'url': '/file/2',
                    'id': 'id2',
                    'size': 150,
                    'parentId': 'id1',
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 400, response.json()


async def test_imports_post_parent_no_folder_update(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FOLDER',
                    'id': 'id_cat',
                },
                {
                    'type': 'FILE',
                    'url': '/file/1',
                    'id': 'id1',
                    'size': 100,
                },
                {
                    'type': 'FILE',
                    'url': '/file/2',
                    'id': 'id200',
                    'size': 200,
                    'parentId': 'id_cat',
                },
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 200, response.json()

    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FILE',
                    'url': '/file/2',
                    'id': 'id200',
                    'size': 200,
                    'parentId': 'id1',
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 400, response.json()


async def test_imports_post_parent_ok(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FOLDER',
                    'id': 'id1',
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 200, response.json()

    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FILE',
                    'url': '/file/1',
                    'id': 'id2',
                    'size': 150,
                    'parentId': 'id1',
                }
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 200, response.json()


async def test_imports_post_error_in_last(client):
    response = await client.post(
        '/imports',
        json={
            'items': [
                {
                    'type': 'FOLDER',
                    'id': 'id1',
                },
                {
                    'type': 'FILE',
                    'url': '/file/wrong',
                    'id': 'id2',
                },
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
    )
    assert response.status_code == 400, response.json()

    response = await client.get('/nodes/id1')
    assert response.status_code == 404, response.json()

    response = await client.get('/nodes/id2')
    assert response.status_code == 404, response.json()
