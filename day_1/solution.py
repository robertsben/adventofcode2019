from typing import List
from math import floor


def get_input() -> str:
    with open('input.txt') as f:
        return f.read()


def calculate_fuel(mass: int) -> int:
    return mass // 3 - 2


def calculate_total(masses: List[int]) -> int:
    return sum(calculate_fuel(mass) for mass in masses)


def solve():
    masses = [int(mass) for mass in get_input().splitlines()]
    return calculate_total(masses)


if __name__ == '__main__':
    print(solve())
