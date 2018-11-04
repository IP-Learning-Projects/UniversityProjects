from search import EightPuzzle


class EightPuzzleMiss(EightPuzzle):
    def h(self, node):
        """ Return the heuristic value for a given state. Default heuristic function used is
        h(n) = number of misplaced tiles """
        return sum(s != g for (s, g) in zip(node.state, self.goal))
    
        
class EightPuzzleMht(EightPuzzle):
    def h(self, node):
        """ Implement Manhattan distance. Hint! Look at
        Missplaced Tiles heuristic function above """
        return sum(abs(e - s) for s, e in zip(node.state, self.goal))
