def messageToBits(message):
    return [int(bit) for char in message for bit in format(ord(char), '08b')]

def bitsToMessage(msgByte):
    msgInt = 0
    index = 0
    

    i = 128
    while (i > 0):
        msgInt += (i * msgByte[index])
        index += 1
        i = i // 2
    
    msgChar = chr(msgInt)
    return msgChar

def encodeFile(infile, message, outfile, offset):
    msgBits = messageToBits(message)
    try:
        with open(infile, "rb") as in_f, open(outfile, "wb") as out_f:
    
            byte = in_f.read(1)
            for x in range(offset):
                out_f.write(byte)
                byte = in_f.read(1)
            
            for i in range(len(msgBits)):
                byte_value = byte[0]

                modified_byte = byte_value ^ msgBits[i]


                out_f.write(bytes([modified_byte]))

                byte = in_f.read(1)

            while byte:
                out_f.write(byte)
                byte = in_f.read(1)

    except FileNotFoundError:
        print("The original file was not found.")
    except IOError as e:
        print(f"An I/O error occured: {e}")

def decodeFile(file1, file2, offset):
    msgByte = []
    finalMessage = ""
    print("Your secret message is: ")
    try: 
        with open(file1, "rb") as f1_f, open(file2, "rb") as f2_f:

            f1_f.seek(offset)
            f2_f.seek(offset)

            byte1 = f1_f.read(1)
            byte2 = f2_f.read(1)

            position = 0
            msgEnd = 0

            while (msgEnd < 16):
                msgIndex = position % 8
                intByte1 = byte1[0]
                intByte2 = byte2[0]

                msgBit = intByte1 ^ intByte2
                
                msgByte.append(0 if msgBit == 0 else 1)
                
                if (msgBit == 0):
                    msgEnd += 1
                else:
                    msgEnd = 0


                if (msgIndex == 7):
                    finalMessage += bitsToMessage(msgByte)
                    msgByte = []

                byte1 = f1_f.read(1)
                byte2 = f2_f.read(1)
                position += 1
        print(finalMessage)
        
    except FileNotFoundError:
        print("One of the files was not found.")
    except IOError as e:
        print(f"An I/O error occured: {e}")

def get_filename(filetype):
    filename = input(f"enter the {filetype} file name (ex: picture.ppm): ")
    return filename

def main():
    message = "hello this is a test of a really long message so lets ee what happens. Oops that should say see, that wasn't an issue decoding it was just a typing error. Im now going to write osme numbers 232432 j233. Heres an excalamtion point:! Ok lets run it."
    offset = 99
    print("")
    try:
        choice = int(input("Choose an option: Encode (1) or Decode(2): "))
    except ValueError:
        print("Invalid input. Please choose a number (1) or (2).")
        return

    if choice == 1:
        infile = get_filename("input")
        outfile = "encoded.ppm"

        encodeFile(infile, message, outfile, offset)
        print("Your file with a secret message is: encoded.ppm")

    elif choice == 2:
        file1 = get_filename("first")
        file2 = get_filename("second")

        decodeFile(file1, file2, offset)

    else:
        print("Invalid input. Please choose a number (1) or (2).")

if __name__ == "__main__":
    main()

