package main

import (
    "fmt"
    "os"
)

func main() {
    var input int
    var originalFile string
    var encodedFile string = "encoded.png"
    
    fmt.Print("Choose an option: Encode (1) or Decode(2): ")
    fmt.Scan(&input)
    fmt.Print("What is the original file? (ex: picture.png): ")
    fmt.Scan(&originalFile)
    
    //decodedMsg := "decoded.txt"
    message := "Hi"
    offset := 99
    
    original, _ := os.ReadFile(originalFile)

    switch input {
    case 1:
    // this section is for encoding
    encoded := EncodeStego(original, message, offset)
    os.WriteFile(encodedFile, encoded, 0644)
    fmt.Println("Encoded message.")

    case 2:
    // this section is for decoding
    fmt.Print("What is the encoded file? (ex: encoded.png): ")
    fmt.Scan(&encodedFile)
    encodedData, _ := os.ReadFile(encodedFile)
    decoded := DecodeStego(original, encodedData, offset)
    fmt.Println("Decoded message:", decoded)
    }
}
