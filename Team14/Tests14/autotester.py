import os
from collections import Counter

QUERY_TAG = "<query>"
SUCCESS_TAG = "<passed/>"
FAILURE_TAG = "</failed>"
SUCCESS_EXIT_CODE = 0
TEST_SETTINGS = {
    "milestone1": True,
    "milestone2": False,
    "milestone3": False,
}
TEST_DIR = "./Tests14"
AUTOTESTER_PATH = "./Code14/build/src/autotester/autotester"
OUTPUT_PATH = "./Tests14/out.xml"


def validate_files(path, source_files, queries_files, keys):
    missing_files = []
    for dir_path, directories, filenames in os.walk(path):
        prefix = dir_path.split(path, 1)[1]
        for filename in filenames:
            if filename.endswith("_source.txt"):
                source_key = prefix + "/" + filename.rsplit("_source.txt", 1)[0]
                source_files[source_key] = os.path.join(dir_path, filename)
            elif filename.endswith("_queries.txt"):
                queries_key = prefix + "/" + filename.rsplit("_queries.txt", 1)[0]
                queries_files[queries_key] = os.path.join(dir_path, filename)

        for key in source_files.keys():
            if key not in queries_files:
                missing_files.append(f"{key}_queries.txt")
            else:
                keys.add(key)

        for key in queries_files.keys():
            if key not in source_files:
                missing_files.append(f"{key}_source.txt")
            else:
                keys.add(key)

    if len(missing_files) > 0:
        raise Exception("Missing files: " + ", ".join(missing_files))
    else:
        print(f"Found {len(keys)} sets of System Tests")


def run_tests(source_files, queries_files, keys, failures):
    for key in keys:
        print(f"Running System Test {key}...")
        execute(key, source_files[key], queries_files[key])
        validate_output(key, failures)
        clean_up()


def execute(key, source_filepath, query_filepath):
    if not os.path.exists(source_filepath):
        raise Exception(f"Missing path {source_filepath}")
    if not os.path.exists(query_filepath):
        raise Exception(f"Missing path {query_filepath}")

    command = f'{AUTOTESTER_PATH} {source_filepath} {query_filepath} {OUTPUT_PATH}'

    command = command + "> /dev/null"

    exit_code = os.system(command)

    if exit_code != SUCCESS_EXIT_CODE:
        raise Exception(
            f"Autotester execution failed for {key} with exit code: {exit_code}. Please run this test manually to verify.")
    else:
        print(f"Autotester execution successful for {key}")


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
            print(f"All queries passed for {key}!")
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
            keys = set()
            failures = []

            validate_files(os.path.join(TEST_DIR, test_set), source_files, queries_files, keys)
            run_tests(source_files, queries_files, keys, failures)

            if len(failures) > 0:
                raise Exception(f"System Tests failed for {len(failures)} sets in {test_set}: " + ", ".join(failures))
            else:
                print(f"All System Tests passed for {test_set}!\n")


if __name__ == "__main__":
    run()
