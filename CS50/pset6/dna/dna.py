import sys
import csv

def maxrepeat (s, sub):
    longest_run = 0
    for i in range(len(s)):
        count = 0
        while True:
            start = i + count * len(sub)
            end = start + len(sub)

            if s[start:end] == sub:
                count += 1
                longest_run = max(longest_run, count)
                
            else:
                break

    return longest_run


def main():
    if len(sys.argv) == 1 or len(sys.argv) > 3:
        print("Usage: dna /{databases}/... /{sequences}/...")
        exit(0)

    database = []
    with open(sys.argv[1], 'r') as file:
        reader = csv.DictReader(file)

        for row in reader:
            database.append(row)


    with open(sys.argv[2], 'r') as file:
        txtfile = file.read()

    str = list(database[0].keys())[1:]

    result = {}
    for collum in str:
        result[collum] = maxrepeat(txtfile, collum)


    for pessoa in database:
        match = 0
        for collum in str:
            if int(pessoa[collum]) == result[collum]:
                match += 1

        if match == len(str):
            print(pessoa["name"])
            return

    print("no match")
    return
main()