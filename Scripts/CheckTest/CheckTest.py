import json
import re
import subprocess
from pathlib import Path

JSON_FILE_PATH = "../../Test/Compilation/Result/Result.json"
TEST_DIR_PATH = "../../Test/Compilation"
EXE_PATH = "../../cmake-build-debug/RyntraProject.exe"

def strip_ansi_sequences(text):
    ansi_escape_seq = re.compile(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])')
    return ansi_escape_seq.sub('', text)

def load_test_cases(json_path):
    try:
        with open(json_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
        return { case['fileName']: case for case in data['Result'] }
    except Exception as e:
        print(f"Cannot read json file because: {e}")
        return {}

def normalize_output(output_str):
    output_str = strip_ansi_sequences(output_str)
    if not output_str.strip():
        return []
    return [line.strip() for line in output_str.strip().split('\n')]

def run_single_test(file_path, test_case):
    expect_output = test_case['expectOutput']
    test_input = test_case.get('input', [])

    try:
        input_str = "\n".join(test_input) if test_input else None

        result = subprocess.run(
            [EXE_PATH, str(file_path)],
            input=input_str,
            capture_output=True,
            text=True,
            timeout=10
        )

        actual_output = normalize_output(result.stdout)

        if isinstance(expect_output, str):
            expected_list = normalize_output(expect_output)
        else:
            expected_list = expect_output

        if actual_output == expected_list:
            print(f"Pass: {file_path.name}")
            return True
        else:
            print(f"Fail: {file_path.name}")
            print(f"    Expected: {expected_list}")
            print(f"    Actual: {actual_output}")

            if result.stderr:
                print(f"    With Error: {result.stderr.strip()}")
            return False

    except subprocess.TimeoutExpired:
        print(f"Timeout: {file_path.name} run too long")
        return False

    except Exception as e:
        print(f"Run error: {file_path.name}, with description: {e}")
        return False
def main():
    print("---- Start Test ----")
    test_cases = load_test_cases(JSON_FILE_PATH)
    if not test_cases:
        return

    test_dir = Path(TEST_DIR_PATH)
    if not test_dir.exists():
        print(f"Test folder {TEST_DIR_PATH} doesn't exist!")
        return

    passed_count = 0
    total_count = 0

    for file in test_dir.rglob("*.rynt"):
        file_name = file.name
        if file_name in test_cases:
            total_count += 1
            if run_single_test(file, test_cases[file_name]):
                passed_count += 1
        else:
            print(f"Skip {file_name} because there's no matching test case in JSON")

    print("\n---- Summary ----")
    print(f"Passed: {passed_count} / {total_count}")

if __name__ == "__main__":
    main()