import utils
import mechanics


def calculateNeed(alloc, max):
    rows = len(alloc)
    cols = len(alloc[0])
    need = [[0 for _ in range(cols)] for _ in range(rows)]

    for i in range(rows):
        for j in range(cols):
            need[i][j] = max[i][j] - alloc[i][j]

    return need


def tableView1(alloc, max, need, available):
    rows = len(alloc)
    cols = len(alloc[0])

    print("Available: ", end="")
    for i in range(len(available)):
        print(available[i], end=" ")
    print()

    print("Alloc\t\tMax\t\tNeed")

    dashes = ["-"] * 45
    print("".join(dashes))

    for i in range(rows):
        # print alloc
        for j in range(cols):
            print(alloc[i][j], end=" ")
        print("\t\t", end="")
        # print max
        for j in range(cols):
            print(max[i][j], end=" ")
        print("\t\t", end="")
        # print need
        for j in range(cols):
            print(need[i][j], end=" ")
        print()


def tableView2(alloc, max, need, request, available):
    rows = len(alloc)
    cols = len(alloc[0])

    print("Available: ", end="")
    for i in range(len(available)):
        print(available[i], end=" ")
    print()

    print("Alloc\t\tMax\t\tNeed\t\tRequest")

    dashes = "-" * 60
    print(dashes)

    for i in range(rows):
        # print alloc
        for j in range(cols):
            print(alloc[i][j], end=" ")
        print("\t\t", end="")
        # print max
        for j in range(cols):
            print(max[i][j], end=" ")
        print("\t\t", end="")
        # print need
        for j in range(cols):
            print(need[i][j], end=" ")
        print("\t\t", end="")
        # print request
        for j in range(cols):
            print(request[i][j], end=" ")
        print()


def safety_check(alloc, need, available):
    # init
    work = []
    safeSeq = []
    P = len(alloc)
    R = len(alloc[0])

    finished = [False] * len(alloc)

    # work = available
    for i in range(len(available)):
        work.append(available[i])

    # safe sequence init
    for i in range(P):
        safeSeq.append(0)

    # While all processes are not finished or system is not in safe state.
    index = 0
    while index < P:
        # Find a process which is not finish and whose needs can be satisfied with
        # current work[] resources.
        found = False
        for i in range(P):
            # Check if a process is finished
            if not finished[i]:
                # need[i] > work: break
                j = 0
                while j < R:
                    if need[i][j] > work[j]:
                        break
                    j += 1

                if j == R:
                    # free resources
                    for k in range(R):
                        work[k] += alloc[i][k]

                    # add to safe sequence
                    safeSeq[index] = i
                    index += 1

                    # mark as finished
                    finished[i] = True
                    found = True

        if not found:
            print("System is not in a safe state")
            return False

    print("System is in a safe state.\nSafe sequence is: ", end="")
    for i in range(P):
        print("P" + str(safeSeq[i]) + " ", end="")

    return True


def resource_allocation(alloc, max, need, available, i):
    R = len(alloc[0])

    request = []

    print("Request: ")
    for k in range(R):
        tmp = int(input())
        request.append(tmp)

    if not utils.compare(request, R, need, i):
        print("Overflow. Resources cannot be allocated.")
        return False
    else:
        if utils.compare(request, available, R):
            for j in range(R):
                available[j] -= request[j]
                alloc[i][j] += request[j]
                need[i][j] -= request[j]
            mechanics.table_view(alloc, max, need, available)
            is_safe = safety_check(alloc, need, available)
            if is_safe:
                print("Resources allocated immediately.")
                return True
            else:
                for j in range(R):
                    available[j] += request[j]
                    alloc[i][j] -= request[j]
                    need[i][j] += request[j]
                print("Resources cannot be allocated immediately.")
                return False
        else:
            print("Resources cannot be allocated.")
            return False
