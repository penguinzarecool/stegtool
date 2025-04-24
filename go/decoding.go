package main

func bitsToMessage(bits []byte) string {
    msg := []byte{}
    for i := 0; i < len(bits); i += 8 {
        if i+8 > len(bits) {
            break
        }
        var c byte = 0
        for j := 0; j < 8; j++ {
            c = (c << 1) | bits[i+j]
        }
        msg = append(msg, c)
    }
    return string(msg)
}

func DecodeStego(original, encoded []byte, offset int) string {
    bits := []byte{}
    max := len(original)
    if len(encoded) < max {
        max = len(encoded)
    }

    var endCtr int = 0
    //for i := offset; i < max; i++ {
    for i := offset; endCtr < 8; i++ {
        bit := (original[i] ^ encoded[i])
        if bit == 0 {
            endCtr++
        } else {
            endCtr = 0
        }
        bits = append(bits, bit)
    }

    return bitsToMessage(bits)
}

