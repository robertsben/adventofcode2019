package main

import (
	"fmt"
	"io/ioutil"
	"strings"
)

func getInput() string {
	masses, _ := ioutil.ReadFile("input.txt")
	return string(masses)
}

func calculateFuelForMass(mass int) int {
	return mass / 3 - 2
}

func calculateFuelWithFuel(mass int)

func solve() int {
	masses := strings.Split(getInput(), "\n")
}

func main() {
	fmt.Println("Hello, world!")
}
