import binascii
import math
import csv

f = open("processarImg.BMP", "rb")

size = 0

try:
	byte = f.read(1)
	while byte != "":
		byte = f.read(1)
		size = size + 1
		# print(byte)
finally:
	f.close()

print("Total file size in bytes" + str(size))

f = open("processarImg.BMP", "rb")

mybytes = []

try:
	byte = f.read(1)
	mybytes.append(byte)
	while byte != "":
		byte = f.read(1)
		if byte != "":
			mybytes.append(byte)
finally:
	f.close()

print("Total Length of bytes array " + str(len(mybytes)))

myhex = []

f = open("processarImg.BMP", "rb")

try:
	byte = f.read(1)
	myhex.append(binascii.hexlify(byte))
	while byte != "":
		byte = f.read(1)
		if byte != "":
			myhex.append(binascii.hexlify(byte))
finally:
	f.close()

print("Total Length of hex array " + str(len(myhex)))

with open('eggs.csv', 'wb') as csvfile:
    spamwriter = csv.writer(csvfile, delimiter=' ', quotechar='|')
    spamwriter.writerow(myhex)

print("Most likely done!")
