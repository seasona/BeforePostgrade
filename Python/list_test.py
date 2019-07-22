import sys


def main():
    list2 = ['test', 'seem', 'title']
    print(sys.getsizeof(list2))
    for member in list2:
        print(member.title(), end=' ')
    map = {'test': 354, 'red': 34, 'blue': 45}
    map.pop('test')
    print(map)


main()
