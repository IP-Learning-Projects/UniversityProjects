import time
from eight_puzzle import *
from search import *
import random


global answer
global mlist
global glist
mlist=[]
glist=[]
# menu used to generate a puzzle and it's solution based on user input
# the appropriate changes were made in search.py in order to extend the puzzle to N
def userMenu():
    global answer
    global mlist
    global glist
    answer = input("do you want a Random puzzle or a Predefined one, or do you want to type one Manually? r/p/m")
    if answer == 'm' :
        var = int(input("how many pieces do you want to have in the puzzle?"))
        while not math.sqrt(var + 1).is_integer():
            var = int(input("how many pieces do you want to have in the puzzle?"))
        N_init(var)
        mlist = input("insert problem")
        mlist = mlist.split(',')
        for x in range(0, len(mlist)):
            mlist[x] = int(mlist[x])
        glist = input("insert goal")
        glist = glist.split(',')
        for x in range(0, len(glist)):
            glist[x] = int(glist[x])

    if answer == 'r' :
        var = random.randint(8,100)

        while not math.sqrt(var + 1).is_integer():
            var = random.randint(8, 100)
        print('random puzzle selected:',var)
        N_init(var)
        print('mlist:',len(mlist))
        while len(mlist) <= var :
            rand = random.randint(0 , var)
            if rand not in mlist :
                mlist.append(rand)
                print(mlist)
        while len(glist) <= var :
            rand = random.randint(0,var)
            if rand not in glist :
                glist.append(rand)

    mlist = tuple(mlist)
    glist = tuple(glist)



def main():
    global answer
    global mlist
    global glist
    userMenu()
    if answer == 'p':
        print('here is a 15 puzzle')
        print('goal:(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,15, 0)')
        print('problem:(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 14, 15)')

        problem_miss = EightPuzzleMiss((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 14, 15),
                                       (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0))

        problem_mht = EightPuzzleMht((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 14, 15),
                                       (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0))
    else:
        problem_miss = EightPuzzleMiss(mlist,glist)
        problem_mht = EightPuzzleMht(mlist,glist)
        print('problem:', mlist)
        print('goal:', glist)
    t1 = time.time()
    path = astar_search(problem_miss).solution()
    t2 = time.time()
    t3 = time.time()
    path2 = astar_search(problem_mht).solution()
    t4 = time.time()

    print(path, '\n', t2 - t1)
    print(path2, '\n', t4 - t3)
    """ Compare searchers """
    compare_searchers(problems=[problem_miss, problem_mht],
                      header=['Searcher', 'A* h1(n)',
                              'A* h2(n)'], searchers=[
            astar_search,
            recursive_best_first_search])


if __name__ == "__main__":
    main()