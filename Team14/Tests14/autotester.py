import os
from collections import Counter
from pathlib import Path

if not os.getenv("AUTOTESTER_PATH"):
    print("Loading .env file...")
    from dotenv import load_dotenv
    if not load_dotenv():
        raise Exception("ERROR: Missing .env file")
    print("Environment variables loaded successfully!")
else:
    print("Using pre-configured environment variables")

MACOS = "posix"
WINDOWS = "nt"
QUERY_TAG = "<query>"
SUCCESS_TAG = "<passed/>"
FAILURE_TAG = "</failed>"
EXIT_SUCCESS = 0
EXIT_FAILURE = 1
SOURCE_SUFFIX = "_source.txt"
QUERIES_SUFFIX = "_queries.txt"
ERROR_PREFIX = "error_"
TEST_SETTINGS = {
    "milestone1": True,
    "milestone2": False,
    "milestone3": False,
}

TEST_DIR = Path(os.getenv("TEST_DIR"))
AUTOTESTER_PATH = Path(os.getenv("AUTOTESTER_PATH"))
OUTPUT_PATH = Path(os.getenv("OUTPUT_PATH"))
NULL_DEVICE = os.getenv("NULL_DEVICE")


def validate_files(path, source_files, queries_files, error_files, valid_keys, error_keys):
    missing_files = []
    for dir_path, directories, filenames in os.walk(path):
        prefix = dir_path.split(path, 1)[1]
        for filename in filenames:
            if filename.startswith(ERROR_PREFIX):
                if filename.endswith(QUERIES_SUFFIX):
                    continue
                error_key = prefix + "/" + filename.rsplit(SOURCE_SUFFIX, 1)[0]
                error_files[error_key] = [os.path.join(dir_path, filename), os.path.join(dir_path, filename.rsplit(SOURCE_SUFFIX, 1)[0] + QUERIES_SUFFIX)]
            elif filename.endswith(SOURCE_SUFFIX):
                source_key = prefix + "/" + filename.rsplit(SOURCE_SUFFIX, 1)[0]
                source_files[source_key] = os.path.join(dir_path, filename)
            elif filename.endswith(QUERIES_SUFFIX):
                queries_key = prefix + "/" + filename.rsplit(QUERIES_SUFFIX, 1)[0]
                queries_files[queries_key] = os.path.join(dir_path, filename)

        for key in source_files.keys():
            if key not in queries_files:
                missing_files.append(f"{key}{QUERIES_SUFFIX}")
            else:
                valid_keys.add(key)

        for key in queries_files.keys():
            if key not in source_files:
                missing_files.append(f"{key}{SOURCE_SUFFIX}")
            else:
                valid_keys.add(key)

        for key in error_files.keys():
            error_keys.add(key)

    if len(missing_files) > 0:
        raise Exception("Missing files: " + ", ".join(missing_files))
    else:
        print(f"Found {len(valid_keys) + len(error_keys)} sets of System Tests")


def run_tests(source_files, queries_files, valid_keys, error_files, error_keys, failures):
    counter = 0
    for key in valid_keys:
        counter += 1
        print(f"Test {counter}: Running Valid System Test {key}...")
        execute(key, source_files[key], queries_files[key])
        validate_output(key, failures)
        clean_up()

    for key in error_keys:
        counter += 1
        print(f"Test {counter}: Running Erroneous System Test {key}...")
        execute_with_error(key, error_files[key], failures)
    print(f"{counter} of {len(valid_keys) + len(error_keys)} tests executed")


def execute(key, source_filepath, query_filepath):
    if not os.path.exists(source_filepath):
        raise Exception(f"Missing path {source_filepath}")
    if not os.path.exists(query_filepath):
        raise Exception(f"Missing path {query_filepath}")

    command = f'{AUTOTESTER_PATH} {source_filepath} {query_filepath} {OUTPUT_PATH}'

    command = f"{command} > {NULL_DEVICE}"

    exit_code = os.system(command)

    if exit_code != EXIT_SUCCESS:
        raise Exception(
            f"Autotester execution failed for {key} with exit code: {exit_code}. Please run this test manually to verify.")
    else:
        print(f"Success: Autotester execution successful for {key}")


def execute_with_error(key, filepaths, failures_list):
    source_path = filepaths[0]
    queries_path = filepaths[1]
    if not os.path.exists(source_path):
        raise Exception(f"Missing path {source_path}")

    command = f'{AUTOTESTER_PATH} {source_path} {queries_path} {OUTPUT_PATH}'

    command = f"{command} > {NULL_DEVICE}"

    exit_code = os.system(command)
    if os.name == MACOS:
        exit_code = os.WEXITSTATUS(exit_code)
    elif os.name == WINDOWS:
        # TODO: Exit code should be 1, but on Windows it is -1073740791
        print(f"WARNING: Exit code should be 1, but on Windows it is -1073740791")
        exit_code = 1 if exit_code == -1073740791 else exit_code

    if exit_code == EXIT_FAILURE:
        print(f"Success: Autotester execution failed for {key} as expected")
    else:
        raise Exception(
            f"Autotester execution failed for {key} with exit code: {exit_code} instead of exit code 1. Test is not failing as expected. Please run this test manually to verify.")


def validate_output(key, failures_list):
    if not os.path.exists(OUTPUT_PATH):
        raise Exception(f"Missing output file {OUTPUT_PATH}")

    with open(OUTPUT_PATH, "r") as f:
        output = f.read()
        text_chunks = Counter(output.split())
        total = text_chunks[QUERY_TAG]
        successes = text_chunks[SUCCESS_TAG]
        failures = text_chunks[FAILURE_TAG]

        print(f"Total queries: {total}; Successful queries: {successes}; Failed queries: {failures}")

        if successes == total:
            print(f"Success: All queries passed for {key}!")
        else:
            failures_list.append(key)
            print(f"ERROR: Failing tests for {key}")


def clean_up():
    os.remove(OUTPUT_PATH)


def run():
    for test_set, to_run in TEST_SETTINGS.items():
        if to_run:
            print(f"Running System Tests for {test_set}...")

            source_files = {}
            queries_files = {}
            error_files = {}
            valid_keys = set()
            error_keys = set()
            failures = []

            validate_files(os.path.join(TEST_DIR, test_set), source_files, queries_files, error_files, valid_keys, error_keys)
            run_tests(source_files, queries_files, valid_keys, error_files, error_keys, failures)

            if len(failures) > 0:
                raise Exception(f"System Tests failed for {len(failures)} sets in {test_set}: " + ", ".join(failures))
            else:
                print(f"Success! All System Tests passed for {test_set}!\n")


if __name__ == "__main__":
    run()
