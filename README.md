# stegtool
This is a steganography tool I've made. It only works on lossless files. It is written in a handful of languages, so find one that suites your fancy and check it out.

The different versions are cross compatible, so if you encrypt something with the python version, you can decrypt it with the C version.
Other than that, the internal mechanisms vary slightly between each version, but they all achieve the same effect.

The encryption/decryption works by one time pad with the LSB of every byte, one byte per bit in the message.
So, if you want to decrypt a message, you need both the modified file and the original file to xor it against. 

For simplicity, only the bash program prompts for a "secret message". Otherwise, you will need to brave the code and find the "message" variable, and change it to say what you want.
I'll fix this in a bit.

***I would suggest .png files, as thats what I designed this project for.***
