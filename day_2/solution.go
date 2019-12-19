package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

type instructionSet struct {
	noun int
	verb int
	instructions []int
}

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

func runInstructions(instructions instructionSet) instructionSet {
	var operationResult int
	var isEndCode bool

	for i := 0; i < len(instructions.instructions) - 4; i += 4 {
		operationResult, isEndCode = runInstruction(instructions.instructions, i)
		if isEndCode {
			break
		}
		instructions.instructions[instructions.instructions[i+3]] = operationResult
	}
	return instructions
}


func amendInstructionsForRun(instructions instructionSet) instructionSet {
	instructions.instructions[1] = instructions.noun
	instructions.instructions[2] = instructions.verb
	return instructions
}

func instructionSetFor(noun int, verb int, rawInput string) instructionSet {
	return instructionSet{noun, verb, convertInstructions(rawInput)}
}

func runInstructionsFor(noun int, verb int) instructionSet {
	return runInstructions(amendInstructionsForRun(instructionSetFor(noun, verb, readInput())))
}

func runAllInstructions(c chan instructionSet) {
	for i := 0; i < 100; i++ {
		for j := 0; j < 100; j++ {
			c <- runInstructionsFor(i, j)
		}
	}
	close(c)
}

func findInstructionSetWithResult(result int) instructionSet {
	var resultInstructions instructionSet
	c := make(chan instructionSet)
	go runAllInstructions(c)
	for i := range c {
		if i.instructions[0] == result {
			resultInstructions = i
		}
	}
	return resultInstructions
}


func main() {
	var part1Results = runInstructionsFor(12, 2)

	var part2Results = findInstructionSetWithResult(19690720)
	result := 100 * part2Results.noun + part2Results.verb

	fmt.Println("Part 1: ", part1Results.instructions[0])
	fmt.Printf("Part 2: %d (noun: %d, verb: %d)\n", result, part2Results.noun, part2Results.verb)
}
