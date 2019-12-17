from typing import List


def never_decreasing(password: str) -> bool:
    return all(password[i] <= password[i+1] for i in range(len(password)-1))


def has_adjacent_duplicates(password: str) -> bool:
    return any(password[i] == password[i+1] for i in range(len(password)-1))


def passes_criteria(password: int) -> bool:
    return never_decreasing(password) and has_adjacent_duplicates(password)


def find_between(start: int, end: int) -> List[int]:
    return [password for password in range(start, end) if passes_criteria(str(password))]


if __name__ == '__main__':
    day_4_input = '347312-805915'
    start, end = day_4_input.split('-')
    print(len(find_between(int(start), int(end))))
