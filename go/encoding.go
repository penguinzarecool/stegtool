package main

import (
    "fmt"
)

func messageToBits(msg string) []byte {
    bits := []byte{}
    
    for _, c := range msg {
//        fmt.Printf("%d ", c)
        for i := 128; i>0; i=i/2 { 
            if (int(c) & i) != 0 {
                bits = append(bits, 1)
            } else {
                bits = append(bits, 0)
            }
        }
    }
 //   fmt.Println(bits)
    return bits
}
// ^^^^^^^^^^^^^^^^^^^^^This is complicated^^^^^^^^^^^^^^^^^^^^^
// heres how it works: 
// each char in msg is stored to c one at a time
// then we loop through 128 64 32 16 8 4 2 1 (2's places)
// for each of these, c is conv to ascii int and bitwise "anded"
// this returns a value >= 0
// this is interpretted as 1 or 0, then added to the bin string
//==============================================================

func EncodeStego(original []byte, message string, offset int) []byte {
    bits := messageToBits(message)
    result := make([]byte, len(original))
    copy(result, original)

    fmt.Printf("\n")
    idx := offset

    for i, bit := range bits {
        idx = offset + i
        if idx >= len(original) {
            break
        }
        origByte := original[idx]
//        fmt.Printf("Byte #%d:\n", idx + 1)
 //       fmt.Println(origByte)
  //      fmt.Println(bit)
        result[idx] = (origByte ^ bit)
   //     fmt.Println(result[idx])
    }
    idx++
    //result[idx] = (result[idx] ^ 1)

    return result
}

