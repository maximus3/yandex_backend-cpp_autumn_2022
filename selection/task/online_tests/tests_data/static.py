from online_tests.unit_test import IMPORT_BATCHES, EXPECTED_TREE

EXPECTED_STATISTIC = {
    'items': [
        {
            'type': 'CATEGORY',
            'url': 'Товары',
            'id': '069cb8d7-bbdd-47d3-ad8f-82ef4c269df1',
            'date': '2022-02-01T12:00:00.000Z',
            'parentId': None,
            'size': None,
        },
        {
            'type': 'CATEGORY',
            'url': 'Товары',
            'id': '069cb8d7-bbdd-47d3-ad8f-82ef4c269df1',
            'date': '2022-02-02T12:00:00.000Z',
            'parentId': None,
            'size': 69999,
        },
        {
            'type': 'CATEGORY',
            'url': 'Товары',
            'id': '069cb8d7-bbdd-47d3-ad8f-82ef4c269df1',
            'date': '2022-02-03T12:00:00.000Z',
            'parentId': None,
            'size': 55749,
        },
        {
            'type': 'CATEGORY',
            'url': 'Товары',
            'id': '069cb8d7-bbdd-47d3-ad8f-82ef4c269df1',
            'date': '2022-02-03T15:00:00.000Z',
            'parentId': None,
            'size': 58599,
        },
    ]
}

IMPORTS_AND_NODES_DATA = [
    (
        {
            'items': [
                {
                    'type': 'CATEGORY',
                    'url': 'Категория',
                    'id': 'id1',
                },
                {
                    'type': 'CATEGORY',
                    'url': 'Подкатегория 1',
                    'id': 'id11',
                    'parentId': 'id1',
                },
                {
                    'type': 'CATEGORY',
                    'url': 'Подкатегория 2',
                    'id': 'id12',
                    'parentId': 'id1',
                },
                {
                    'type': 'OFFER',
                    'url': 'Товар',
                    'id': 'tovar',
                    'size': 100,
                    'parentId': 'id1',
                },
            ],
            'updateDate': '2022-02-01T12:00:00.000Z',
        },
        {
            'type': 'CATEGORY',
            'url': 'Категория',
            'id': 'id1',
            'size': 100,
            'parentId': None,
            'date': '2022-02-01T12:00:00.000Z',
            'children': [
                {
                    'type': 'CATEGORY',
                    'url': 'Подкатегория 1',
                    'id': 'id11',
                    'size': None,
                    'parentId': 'id1',
                    'date': '2022-02-01T12:00:00.000Z',
                    'children': [],
                },
                {
                    'type': 'CATEGORY',
                    'url': 'Подкатегория 2',
                    'id': 'id12',
                    'size': None,
                    'parentId': 'id1',
                    'date': '2022-02-01T12:00:00.000Z',
                    'children': [],
                },
                {
                    'type': 'OFFER',
                    'url': 'Товар',
                    'id': 'tovar',
                    'size': 100,
                    'parentId': 'id1',
                    'date': '2022-02-01T12:00:00.000Z',
                    'children': None,
                },
            ],
        },
    ),
    (
        {
            'items': [
                {
                    'type': 'OFFER',
                    'url': 'Товар',
                    'id': 'tovar',
                    'size': 100,
                    'parentId': 'id11',
                }
            ],
            'updateDate': '2022-02-01T13:00:00.000Z',
        },
        {
            'type': 'CATEGORY',
            'url': 'Категория',
            'id': 'id1',
            'size': 100,
            'parentId': None,
            'date': '2022-02-01T13:00:00.000Z',
            'children': [
                {
                    'type': 'CATEGORY',
                    'url': 'Подкатегория 1',
                    'id': 'id11',
                    'size': 100,
                    'parentId': 'id1',
                    'date': '2022-02-01T13:00:00.000Z',
                    'children': [
                        {
                            'type': 'OFFER',
                            'url': 'Товар',
                            'id': 'tovar',
                            'size': 100,
                            'parentId': 'id11',
                            'date': '2022-02-01T13:00:00.000Z',
                            'children': None,
                        }
                    ],
                },
                {
                    'type': 'CATEGORY',
                    'url': 'Подкатегория 2',
                    'id': 'id12',
                    'size': None,
                    'parentId': 'id1',
                    'date': '2022-02-01T12:00:00.000Z',
                    'children': [],
                },
            ],
        },
    ),
    (
        {
            'items': [
                {
                    'type': 'OFFER',
                    'url': 'Товар',
                    'id': 'tovar',
                    'size': 100,
                    'parentId': 'id12',
                }
            ],
            'updateDate': '2022-02-01T14:00:00.000Z',
        },
        {
            'type': 'CATEGORY',
            'url': 'Категория',
            'id': 'id1',
            'size': 100,
            'parentId': None,
            'date': '2022-02-01T14:00:00.000Z',
            'children': [
                {
                    'type': 'CATEGORY',
                    'url': 'Подкатегория 1',
                    'id': 'id11',
                    'size': None,
                    'parentId': 'id1',
                    'date': '2022-02-01T14:00:00.000Z',
                    'children': [],
                },
                {
                    'type': 'CATEGORY',
                    'url': 'Подкатегория 2',
                    'id': 'id12',
                    'size': 100,
                    'parentId': 'id1',
                    'date': '2022-02-01T14:00:00.000Z',
                    'children': [
                        {
                            'type': 'OFFER',
                            'url': 'Товар',
                            'id': 'tovar',
                            'size': 100,
                            'parentId': 'id12',
                            'date': '2022-02-01T14:00:00.000Z',
                            'children': None,
                        }
                    ],
                },
            ],
        },
    ),
]
