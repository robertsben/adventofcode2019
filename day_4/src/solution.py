from typing import List, Callable


def never_decreasing(password: str) -> bool:
    return all(password[i] <= password[i+1] for i in range(len(password)-1))


def has_adjacent_duplicates(password: str) -> bool:
    return any(password[i] == password[i+1] for i in range(len(password)-1))


def has_isolated_adjacent_duplicates(password: str) -> bool:
    return any(
        password[i] == password[i + 1] and password[i] not in (
            password[i-1] if i > 0 else None,
            password[i+2] if i < len(password) - 2 else None
        )
        for i in range(len(password) - 1)
    )


def passes_criteria(password: int, criteria: List[Callable[[bool], str]], ) -> bool:
    return all(criterion(password) for criterion in criteria)


def find_between(start: int, end: int, criteria: List[Callable[[bool], str]]) -> List[int]:
    return [password for password in range(start, end) if passes_criteria(str(password), criteria)]


if __name__ == '__main__':
    day_4_input = '347312-805915'
    start, end = day_4_input.split('-')
    part_1 = find_between(int(start), int(end), (never_decreasing, has_adjacent_duplicates))
    part_2 = find_between(int(start), int(end), (never_decreasing, has_isolated_adjacent_duplicates))
    # print(f'In 1: {part_1}')
    # print(f'In 2: {part_2}')
    print(f'Part 1: {len(part_1)}')
    print(f'Part 2: {len(part_2)}')
