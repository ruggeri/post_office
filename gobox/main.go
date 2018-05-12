package main

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"sync"
	"time"
)

const sleepMillis = 1000

var wg sync.WaitGroup

type threadsMap map[int]chan int

func runListener(c <-chan int) {
	defer wg.Done()
	for {
		val := <-c
		fmt.Println(val)
	}
}

func runProducer(tm threadsMap) {
	defer wg.Done()
	numThreads := len(tm)
	for {
		threadNum := rand.Intn(numThreads)
		tm[threadNum] <- int(rand.Int31())

		sm := rand.Float32() * 2 * sleepMillis
		time.Sleep(time.Duration(sm) * time.Millisecond)
	}
}

func main() {
	numThreads, err := strconv.Atoi(os.Args[1])

	if err != nil {
		panic(err)
	}

	tm := make(threadsMap)

	for idx := 0; idx < numThreads; idx++ {
		c := make(chan int)
		tm[idx] = c

		wg.Add(1)
		go runListener(c)
	}

	for idx := 0; idx < numThreads; idx++ {
		wg.Add(1)
		go runProducer(tm)
	}

	wg.Wait()
}
