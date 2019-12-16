from solution import solve, calculate_fuel


def calculate_total_with_fuel(mass: int) -> int:
    total = 0
    fuel_for_mass = calculate_fuel(mass)
    while fuel_for_mass > 0:
        total += fuel_for_mass
        fuel_for_mass = calculate_fuel(fuel_for_mass)

    return total


if __name__ == '__main__':
    print(solve(calculate_total_with_fuel))
