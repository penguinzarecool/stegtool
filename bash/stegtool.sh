#! /bin/bash

menu() {
    select process in "Information" "Encode" "Decode" "Exit Program"
    do
        case $process in
            "Information") info ;;
            "Encode") encode ;;
            "Decode") decode ;;
            "Exit Program") echo "Exiting program..."; exit 0 ;;
            *) echo "don't do that." ;;
        esac
    done
}

info() {
echo -e "\n\nThis is the information page on Addison's stegtool!\nAddison's Stegtool encodes a (short) secret message into an\n uncompressed pixel file (preferrably .ppm) in such a manner that is is almost\nimpossible to tell that there is a secret message. And, even if the secret\nmessage is revealed, it doesn't matter much, because, using a one-time pad\nmethod, it is impossible to decode the message without the original image.\n\nBefore you start, please make sure that all image files are in the same\ndirectory as the bash executable.\n\nThis project was made to demonstrate my understanding of cryptographic\nsubjects such as steganography and one-time pads, as well as demonstrate\nmy bash scripting abilities.\n\n-Addison Miranda 2025\n\n"
menu
}

encode() {
    echo -e "\nEnter the name of the .ppm you would like to hide your message in. "
    read -p "Make sure that it is in the same directory as this script: " original
    echo -e "\n"
    read -p "Now enter a short secret message: " message
    echo -e "\nencoding...\n"

    orig_offset=99

    str_len=${#message}
    padding=$((str_len % 6))
    for ((i=6; i>padding; i--)); do
        message+=" "
    done

    binary_msg=$(echo -n "$message" | xxd -b | awk '{ for(i=2;i<=7;i++) printf "%s", $i }')
    binary_indiv=$(echo "$binary_msg" | grep -o .)
    msg_len=$(echo "$binary_indiv" | wc -l)


    dd if=$original bs=1 count=$orig_offset of=part1 2>/dev/null
    cat part1 > modified.ppm

    for ((i=0; i<$msg_len; i++)); do
        msg_offset=$(( $msg_len - $i ))
        msg_bit=$(echo "$binary_indiv" | tail -n $msg_offset | head -n 1)
        offset=$(( $orig_offset + $i ))
        dd if=$original bs=1 skip=$offset count=1 of=target_byte 2>/dev/null
        byte=$(xxd -p target_byte)
        dec=$((0x$byte))
        flipped=$((dec ^ msg_bit))
        printf "%b" "$(printf '\\x%02x' "$flipped")" > flipped_byte

        cat flipped_byte >> modified.ppm
    done

    ((offset++))
    dd if=$original bs=1 skip=$offset of=part2 2>/dev/null

    cat part2 >> modified.ppm
    rm target_byte part1 part2 flipped_byte

    echo -e "\nencoding complete!\nWritten to file: modified.ppm\n"
    menu
}

decode() {
    echo -e "\nEnsure that all .ppm's are in this directory.\n"
    read -p "Enter the unaltered .ppm file's full name: " original
    read -p "Now enter the modified .ppm file's full name: " modified
    echo -e "\ndecoding ..."
    echo -e "parsing bytes may take up to 10 seconds ...\n"

    offset=99
    output="tempsecretfile.txt"
    rm -f $output

    endCtr=0
    for ((i=$offset; endCtr<16; i++)); do
        o=$(dd if=$original bs=1 skip=$i count=1 2>/dev/null | tr -d '\0')
        m=$(dd if=$modified bs=1 skip=$i count=1 2>/dev/null | tr -d '\0')
        orig_byte=$(echo $o | xxd -p)
        mod_byte=$(echo $m | xxd -p)
        od=$((0x$orig_byte))
        md=$((0x$mod_byte))

        msg_byte=$((od ^ md))

        if [[ ${msg_byte} -ne 0 ]]; then
            echo -n "1" >> "$output"
            endCtr=0
        else
            echo -n "0" >> "$output"
            ((endCtr++))
        fi

    done

    bin_secret=$(cat $output)

    echo -e "\nyour secret message has been decoded, and is in a file: secretmessage.txt! "
    cat $output | perl -lpe '$_=pack("B*",$_)' > secretmessage.txt
    echo -e "\n"

    rm tempsecretfile.txt

    menu
}


clear
echo -e "Welcome to Addison's Stegtool!\n"
menu
