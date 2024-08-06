import os
import input_reader
import mechanics
import sys

script_dir = os.path.dirname(__file__)

alloc_file_path = os.path.join(script_dir, "alloc.txt")
max_file_path = os.path.join(script_dir, "max.txt")
available_file_path = os.path.join(script_dir, "available.txt")
request_file_path = os.path.join(script_dir, "request.txt")

alloc = input_reader.read_matrix(alloc_file_path)
max = input_reader.read_matrix(max_file_path)
available = input_reader.read_list(available_file_path)
need = mechanics.calculateNeed(alloc, max)
request = input_reader.read_matrix(request_file_path)

mechanics.tableView1(alloc, max, need, available)
print("\n\n")

print("1. Perform safety check.")
print("2. Check if resources allocatable.")
print("3. Deadlock detection.")
print("0. Exit.")
print("Choose an option: ")

n = int(input())

if n == 0:
    sys.exit()
elif n == 1:
    mechanics.safety_check(alloc, need, available)
    sys.exit()
elif n == 2:
    print("Process number: ")
    process = int(input())
    mechanics.resource_allocation(alloc, max, need, available, process)
    sys.exit()
elif n == 3:
    mechanics.tableView2(alloc, max, need, request, available)
    isDeadlocked = mechanics.safety_check(alloc, need, available)
    if isDeadlocked:
        print("No deadlock detected.")
    else:
        print("Deadlock detected.")
    sys.exit()
