import argparse
import pathlib
import subprocess
import sys
import time
import unittest


FILENAME = None
TESTS_DIR = None
TIME_LIMIT = None
TL_ONLY = False
SKIP_CHECK = None
TEST_ONLY = None
STDIN_INPUT = True
INPUT_FILE = None


class Fixture(unittest.TestCase):
    @staticmethod
    def exe_command(filename: pathlib.Path):
        ext = filename.name.split('.')[-1]
        if ext == 'py':
            return f'python {filename}'
        if ext == 'exe':
            return f'{filename}'
        raise RuntimeError(f'No exe command found for {filename}')

    @classmethod
    def setUpClass(cls) -> None:
        if FILENAME is None or TESTS_DIR is None:
            raise RuntimeError('No filename or tests dir')

        cls.command = cls.exe_command(FILENAME)
        cls.right_command = None
        if RIGHT_FILENAME.exists():
            cls.right_command = cls.exe_command(RIGHT_FILENAME)

    def test_all(self):
        avg_time = 0
        cnt = 0
        for file_in in pathlib.Path(TESTS_DIR).glob('*.in'):
            num = file_in.name.split('.')[0]
            if TEST_ONLY and num not in TEST_ONLY:
                continue
            cnt += 1
            file_out_list = str(file_in).split('.')
            file_out_list[-1] = 'out'
            file_out = pathlib.Path('.'.join(file_out_list))

            result_script = None
            if self.right_command:
                with open(file_in) as fin:
                    start_time = time.time()
                    result_script = subprocess.check_output(self.right_command, stdin=fin).decode()
                    time_spent = time.time() - start_time
                    result_script = result_script.replace('\r\n', '\n').strip()
                    print(f'right script ok, {time_spent} sec')

            result_file = None
            if file_out.exists():
                with open(file_out) as fout:
                    result_file = fout.read()

            if result_file and result_script:
                self.assertEqual(result_file.strip(), result_script.strip(), msg=f'Error in script {file_in.name}')

            expexted = result_file or result_script

            with open(file_in) as fin:
                if not STDIN_INPUT:
                    print(f'Creating {INPUT_FILE} file')
                    with open(INPUT_FILE, 'w') as f:
                        f.write(fin.read())
                    print(f'Created')
                    fin = None
                start_time = time.time()
                result = subprocess.check_output(self.command, stdin=fin).decode()
                time_spent = time.time() - start_time
                result = result.replace('\r\n', '\n').strip()
                if not STDIN_INPUT:
                    INPUT_FILE.unlink()

            check_correct = False
            if not TL_ONLY and (SKIP_CHECK is None or num not in SKIP_CHECK):
                check_correct = True
                self.assertEqual(expexted.strip(), result.strip(), msg=f'Error in {file_in.name}')

            self.assertTrue(time_spent < TIME_LIMIT, msg=f'Answer OK, TL in {file_in.name}: {time_spent} sec')
            avg_time += time_spent

            print(file_in, f'OK, check={check_correct}, {time_spent} sec')

        print(f'Average time: {avg_time / cnt} sec')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument('path', type=str, help='Path for dir with tests')
    parser.add_argument('file', type=str, help='Path for executable file')
    parser.add_argument('--tl', type=int, default=1, help='Time limit for tests')
    parser.add_argument('--input', type=str, default='stdin', help='Input file or stdin')
    parser.add_argument('--tl-only', action='store_true', help='Only check time limit')
    parser.add_argument('--skip-check', nargs='+', help='Skip check correct answer for files')
    parser.add_argument('--test-only', nargs='+', help='Only check tests with numbers')

    args = parser.parse_args()

    FILENAME = pathlib.Path(args.file)
    RIGHT_FILENAME = pathlib.Path(args.path) / 'right.py'
    TESTS_DIR = pathlib.Path(args.path)
    STDIN_INPUT = True if args.input == 'stdin' else False
    INPUT_FILE = pathlib.Path(args.input) if not STDIN_INPUT else None

    TIME_LIMIT = args.tl
    TL_ONLY = args.tl_only
    SKIP_CHECK = args.skip_check
    TEST_ONLY = args.test_only

    unittest.main(argv=sys.argv[:1])
