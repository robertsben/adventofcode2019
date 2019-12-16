FROM golang:1.13-alpine AS builder

COPY solution.go .

RUN go build -o solution


FROM alpine

COPY --from=builder /go/solution .

CMD ["./solution"]
