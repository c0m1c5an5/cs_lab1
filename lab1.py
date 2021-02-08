import sys, io, math, os

if len(sys.argv) < 2:
    exit(1)

filename = sys.argv[1]
text_file = io.open(filename, "r", encoding="utf-8")
dictionary = {}

if not text_file:
    exit(1)
 
while True:
    line = text_file.readline()

    if not line:
        text_file.close()
        break

    for char in line:
        if char in dictionary: 
            dictionary[char] += 1
        else: 
            dictionary[char] = 1


sorted_dictionary = sorted(dictionary.items(), key=lambda item: item[1], reverse=True)

number_of_characters = 0
number_of_unique = len(dictionary)

for k, v in dictionary.items():
    number_of_characters += v

entropy = 0.0

for k, v in dictionary.items():
    probability = float(v) / float(number_of_characters)
    entropy += probability * math.log(probability,2)

entropy = entropy * -1

print("File name: " + filename)
print("File size: " + str(os.path.getsize(filename)) + " bytes")
print("Information amount: " + str(number_of_characters * entropy / 8) + " bytes")
print("Number of characters: " + str(number_of_characters))
print("Number of unique characters " + str(number_of_unique))
print("Entropy: " + str(entropy) + "\n")

for char_tuple in sorted_dictionary:

    char = char_tuple[0]
    number = char_tuple[1]
    char_probability = float(number) / float(number_of_characters)
    
    if ord(char) == 10:
        char_name = '\\n'
    else:
        char_name = char
    
    print(char_name + "\t" + str(ord(char)) + "\t" + str(number) + "\t" + str(char_probability * 100))
