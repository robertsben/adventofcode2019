package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

func readInput() string {
	data, _ := ioutil.ReadFile("input.txt")
	return string(data)
}

func convertInstructions(input string) []int {
	data := strings.Split(input, ",")
	instructions := make([]int, len(data))
	for idx, instruction := range data {
		opCode, _ := strconv.Atoi(instruction)
		instructions[idx] = opCode
	}
	return instructions
}

func operationFactory (operand int, operatorA int, operatorB int) (value int, isEnd bool) {
	switch operand {
	case 1:
		value, isEnd = operatorA + operatorB, false
	case 2:
		value, isEnd = operatorA * operatorB, false
	case 99:
		value, isEnd = 0, true
	}
	return
}

func runInstruction(instructions []int, startIndex int) (value int, isEnd bool) {
	var operatorA int = instructions[instructions[startIndex+1]]
	var operatorB int = instructions[instructions[startIndex+2]]
	value, isEnd = operationFactory(instructions[startIndex], operatorA, operatorB)
	return
}

func runInstructions(instructions []int) []int {
	var operationResult int
	var isEndCode bool

	for i := 0; i < len(instructions) - 4; i += 4 {
		operationResult, isEndCode = runInstruction(instructions, i)
		if isEndCode {
			break
		}
		instructions[instructions[i+3]] = operationResult
	}
	return instructions
}

func main() {
	var results = runInstructions(convertInstructions(readInput()))

	fmt.Println(results)
	fmt.Println(results[0])
}
