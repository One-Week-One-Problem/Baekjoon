'''외판원 순회 문제는 영어로 Traveling Salesman problem (TSP) 라고 불리는 문제로 computer science 분야에서 가장 중요하게 취급되는 문제 중 하나이다. 여러 가지 변종 문제가 있으나, 여기서는 가장 일반적인 형태의 문제를 살펴보자.

1번부터 N번까지 번호가 매겨져 있는 도시들이 있고, 도시들 사이에는 길이 있다. (길이 없을 수도 있다) 이제 한 외판원이 어느 한 도시에서 출발해 N개의 도시를 모두 거쳐 다시 원래의 도시로 돌아오는 순회 여행 경로를 계획하려고 한다. 단, 한 번 갔던 도시로는 다시 갈 수 없다. (맨 마지막에 여행을 출발했던 도시로 돌아오는 것은 예외) 이런 여행 경로는 여러 가지가 있을 수 있는데, 가장 적은 비용을 들이는 여행 계획을 세우고자 한다.

각 도시간에 이동하는데 드는 비용은 행렬 W[i][j]형태로 주어진다. W[i][j]는 도시 i에서 도시 j로 가기 위한 비용을 나타낸다. 비용은 대칭적이지 않다. 즉, W[i][j] 는 W[j][i]와 다를 수 있다. 모든 도시간의 비용은 양의 정수이다. W[i][i]는 항상 0이다. 경우에 따라서 도시 i에서 도시 j로 갈 수 없는 경우도 있으며 이럴 경우 W[i][j]=0이라고 하자.

N과 비용 행렬이 주어졌을 때, 가장 적은 비용을 들이는 외판원의 순회 여행 경로를 구하는 프로그램을 작성하시오.'''


def checker(list, value):
    for i in range(len(list)):
        if list[i] == value:
            return False
    return True


def combination(base_city_list, present_city_list, depth):
    if depth == len(base_city_list):
        return present_city_list
    else:
        k = 1
        i = 0
        while i < factorial(len(base_city_list) - 1):
            if k == len(base_city_list):
                k = 1
            else:
                j = 0
                while j < factorial(len(base_city_list) - (depth + 1)):
                    if k == len(base_city_list):
                        k = 1
                    if checker(present_city_list[i], base_city_list[k]):
                        present_city_list[i][depth] = base_city_list[k]
                        i += 1
                        j += 1
                    else:
                        k += 1
                k += 1
        return combination(base_city_list, present_city_list, depth + 1)


def shortest_path(cost_matrix, all_city_list):
    result = 100000000
    for i in range(len(all_city_list)):
        if result > total_cost(cost_matrix, all_city_list[i]):
            result = total_cost(cost_matrix, all_city_list[i])
    return result


def total_cost(cost_matrix, city_list):
    result = 0
    if cost_matrix[city_list[-1] - 1][city_list[0] - 1] == 0:
        return 100000000
    else:
        result += cost_matrix[city_list[-1] - 1][city_list[0] - 1]
    for i in range(len(city_list) - 1):
        if cost_matrix[city_list[i] - 1][city_list[i + 1] - 1] == 0:
            return 100000000
        else:
            result += cost_matrix[city_list[i] - 1][city_list[i + 1] - 1]
    return result


def factorial(num):
    if num == 1 or num == 0:
        return 1
    else:
        return num * factorial(num - 1)


number_of_city = int(input())

cost_matrix = [[0 for i in range(number_of_city)] for j in range(number_of_city)]

for i in range(number_of_city):
    cost_matrix[i] = list(map(int, input().split()))

city_list = [i for i in range(1, number_of_city + 1)]

init_list = [[1 for i in range(number_of_city)] for j in range(factorial(number_of_city - 1))]

all_city_list = combination(city_list, init_list, 1)

print(shortest_path(cost_matrix, all_city_list))