import os


def read_matrix(file_path):
    with open(file_path, "r") as file:
        matrix = []
        for line in file:
            row = [int(num) for num in line.split()]
            matrix.append(row)
    return matrix


def read_list(file_path):
    with open(file_path, "r") as file:
        line = file.readline()
        number_list = [int(num) for num in line.split()]
    return number_list
