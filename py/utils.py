def compare(lst, R, matrix, i):
    for j in range(R):
        if lst[j] > matrix[i][j]:
            return False
    return True


def compare(request, available, R):
    for j in range(R):
        if request[j] > available[j]:
            return False
    return True
