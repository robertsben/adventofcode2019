FROM golang:1.13-alpine as builder

COPY solution.go .

RUN go build -o solution


FROM alpine

WORKDIR /app

COPY --from=builder /go/solution .

COPY input.txt .
COPY test_1.txt .
COPY test_2.txt .
COPY test_3.txt .

CMD ["./solution"]
