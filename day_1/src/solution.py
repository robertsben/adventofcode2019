from typing import List, Callable


def get_input() -> str:
    with open('input.txt') as f:
        return f.read()


def get_masses() -> List[int]:
    return [int(mass) for mass in get_input().splitlines()]


def calculate_fuel(mass: int) -> int:
    return mass // 3 - 2


def calculate_total(masses: List[int], single_calculator: Callable[[int], int]) -> int:
    return sum(single_calculator(mass) for mass in masses)


def solve(single_calculator: Callable[[int], int]):
    return calculate_total(get_masses(), single_calculator)


def calculate_total_with_fuel(mass: int) -> int:
    total = 0
    fuel_for_mass = calculate_fuel(mass)
    while fuel_for_mass > 0:
        total += fuel_for_mass
        fuel_for_mass = calculate_fuel(fuel_for_mass)

    return total


if __name__ == '__main__':
    print("Part 1: ", solve(calculate_fuel))
    print("Part 2: ", solve(calculate_total_with_fuel))
