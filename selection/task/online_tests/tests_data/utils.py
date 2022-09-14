import json
import subprocess
import datetime as dt


def iso_8601_to_datetime(date_str: str) -> dt.datetime:
    date_str = date_str.lower()
    if date_str[-1] == 'z':
        date_str = date_str[:-1] + '+00:00'
    return dt.datetime.fromisoformat(date_str)


def datetime_to_iso_8601(date_obj: dt.datetime) -> str:
    date_str = date_obj.isoformat()
    if date_str.endswith('+00:00'):
        date_str = date_str[:-6]
    return date_str + '.000Z'


async def clear_used_ids(client, used_ids):  # pragma: no cover
    for used_id in used_ids:
        await client.delete(f'delete/{used_id}')


def sort_items(node):  # pragma: no cover
    if node.get('items'):
        node['items'].sort(key=lambda x: x['date'])


def deep_sort_children(node):  # pragma: no cover
    if node.get('children'):
        node['children'].sort(key=lambda x: x['id'])

        for child in node['children']:
            deep_sort_children(child)


def print_diff(expected, response):  # pragma: no cover
    with open('expected.json', 'w', encoding='utf-8') as f:
        json.dump(expected, f, indent=2, ensure_ascii=False, sort_keys=True)
        f.write('\n')

    with open('response.json', 'w', encoding='utf-8') as f:
        json.dump(response, f, indent=2, ensure_ascii=False, sort_keys=True)
        f.write('\n')

    subprocess.run(
        [
            'git',
            '--no-pager',
            'diff',
            '--no-index',
            'expected.json',
            'response.json',
        ]
    )

    return 'output'
