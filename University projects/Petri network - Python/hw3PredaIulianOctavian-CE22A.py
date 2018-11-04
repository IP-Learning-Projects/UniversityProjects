import os
"""global variables used to save the inputs and the outputs of transition, the cost of the edge and the number of 
points for every node """
nodeDict = {}
petriNet_input = {}
petriNet_output = {}


class Node:
    """class that has the purpose to manage the number of points for each node"""
    def __init__(self, _points):
        self.points = _points

    def add(self, x):
        self.points = self.points + x

    def subtract(self, x):
        self.points = self.points - x

    def printing(self):
        print(self.points)

    def get(self):
        return self.points

    def compare(self, x):
        return self.points < x


def input_option_add_node():
    """utility function to insert more nodes or exit"""
    o = int(input("Choose an option: \n"
                  "1)Add another node \n"
                  "2)Exit \n"
                  ))
    return o


def input_nodes():
    """function used to insert values in the global variables defined above. The insertion is in a dictionary
    based on the model {Transition:[[node,points,cost]]}"""
    n = int(input("Insert number of transitions "))
    for i in range(0, n):
        string = 'T'
        string += str(i + 1)
        o = 1
        k = 0
        temp_list = []
        print("Transition",string,":")
        print("Node - transition  --- Insert the nodes that are connected to the transition as input \n")
        while o == 1:
            node_name = input("Insert node ")
            if node_name not in nodeDict:
                nodeDict[node_name] = Node(int(input("Insert number of points ")))
            weight = int(input("Insert the cost of the transition "))
            temp_list.append([node_name, nodeDict[node_name], weight])
            k = k + 1
            o = input_option_add_node()

        petriNet_input[string] = temp_list
        o = 1
        temp_list = []
        print("Transition - node --- Insert the nodes that are connected to the transition as output \n")

        while o == 1:
            node_name = str(input("Insert node "))
            if node_name not in nodeDict:
                nodeDict[node_name] = Node(int(input("Insert number of points ")))
            weight = int(input("Insert the reward of the transition "))
            temp_list.append([node_name, nodeDict[node_name], weight])
            k = k + 1
            o = input_option_add_node()
        petriNet_output[string] = temp_list


def find_path():
    """Function used to find out it the graph is connected. first it copies the list of nodes in a temporary list
    then runs through each transition and if an output of a transition is the same as the input of another,
    then it will copy all the nodes from those 2 into another list, keeping only unique values
    after it finishes, those 2 lists are compared and if they are the same it means a path connecting
    all nodes and transitions was found"""
    node_in_path = []
    node_list = []
    for keys in nodeDict:
        node_list.append(keys)

    for gate_i in petriNet_input:
        for node_i in petriNet_input[gate_i]:

            for gate_o in petriNet_output:
                for node_o in petriNet_output[gate_o]:
                    if node_o[0] == node_i[0]:
                        if node_o[0] not in node_in_path:
                            node_in_path.append(node_o[0])

                        for node_o1 in petriNet_output[gate_i]:
                            if node_o1[0] not in node_in_path:
                                node_in_path.append(node_o1[0])
                        for node_o1 in petriNet_input[gate_o]:
                            if node_o1[0] not in node_in_path:
                                node_in_path.append(node_o1[0])
                        for node_o1 in petriNet_input[gate_i]:
                            if node_o1[0] not in node_in_path:
                                node_in_path.append(node_o1[0])
                        for node_o1 in petriNet_output[gate_o]:
                            if node_o1[0] not in node_in_path:
                                node_in_path.append(node_o1[0])
    for gate_o in petriNet_output:
        for node_o in petriNet_output[gate_o]:

            for gate_i in petriNet_input:
                for node_i in petriNet_input[gate_i]:

                    if node_o[0] == node_i[0]:
                        if node_i[0] not in node_in_path:
                            node_in_path.append(node_i[0])

                        for node_i1 in petriNet_input[gate_o]:
                            if node_i1[0] not in node_in_path:
                                node_in_path.append(node_i1[0])

                        for node_i1 in petriNet_output[gate_i]:
                            if node_i1[0] not in node_in_path:
                                node_in_path.append(node_i1[0])

                        for node_i1 in petriNet_output[gate_o]:
                            if node_i1[0] not in node_in_path:
                                node_in_path.append(node_i1[0])

                        for node_i1 in petriNet_input[gate_i]:
                            if node_i1[0] not in node_in_path:
                                node_in_path.append(node_i1[0])
    return set(node_in_path) == set(node_list)


def points():
    """Function used to change the number of points in nodes"""
    counting = 0
    for key in petriNet_input:
        k = 1
        for node in petriNet_input[key]:
            if node[1].compare(node[2]):
                k = 0
        if k == 1:
            for node in petriNet_input[key]:
                node[1].subtract(node[2])
            for node in petriNet_output[key]:
                node[1].add(node[2])
        else:
            counting += 1

    if counting != len(petriNet_input):
        points()


def print_net():
    """Function used to print the net"""
    for key in petriNet_input:
        for node in petriNet_input[key]:
            print(node[0], ":", node[1].get(), "pt", "--------", node[2], "------->|", key)
        for node in petriNet_output[key]:
            print(key, "|-------", node[2], "-------->", node[0], ":", node[1].get(), "pt")
        print("\n")


def points_verbose():
    """The verbose counterpart of the points function"""
    counting = 0
    for key in petriNet_input:
        k = 1
        print("Transition", key,":")
        print_net_verbose(key)
        for node in petriNet_input[key]:
            if node[1].compare(node[2]):
                print("Not enough points in node", node[0], "for transition", key,"\n")
                k = 0
        if k == 1:
            for node in petriNet_input[key]:
                node[1].subtract(node[2])
            for node in petriNet_output[key]:
                node[1].add(node[2])
            print("Transition", key, " result:")
            print_net_verbose(key)
        else:
            counting += 1

    if counting != len(petriNet_input):
        os.system('pause')
        points_verbose()


def print_net_verbose(key):
    """The verbose counterpart of the print_net function
    it runs for a given key/transition"""

    for node in petriNet_input[key]:
        print(node[0], ":", node[1].get(), "pt", "--------", node[2], "------->|", key)

    for node in petriNet_output[key]:
        print(key, "|-------", node[2], "-------->", node[0], ":", node[1].get(), "pt")
    print("\n")


def run_petriNet_simulator():
    """Function that runs all the other functions in order to simulate a Petri net"""
    input_nodes()
    print("Initial net:\n")
    print_net()
    x = int(input("1)Do you want the step by step display method ?\n2)Do you want to display the final solution?"))
    if find_path():
        if x == 2:
            points()
        else:
            points_verbose()
    else:
        print("Some parts of the net are isolated.\n")
        if input("Do you want to continue ? \ny/n?") == 'y':
            if x == 2:
                points()
            else:
                points_verbose()
        else:
            print("Process ended.\n")
            if input("Exit program or reset") == "reset":
                main()
                global petriNet_input
                global petriNet_output
                global nodeDict
                petriNet_input = {}
                petriNet_output = {}
                nodeDict = {}
    print("Final net:\n")
    print_net()
    os.system('pause')


def test_function():
    """The test function. runs like run_petriNet_simulator function
     but it has predefined values for nodes, transitions, points and costs"""
    global petriNet_input
    global petriNet_output
    global nodeDict
    P1 = Node(1)
    P2 = Node(2)
    P3 = Node(0)
    nodeDict = {'P1': P1, 'P2': P2, 'P3': P3}
    petriNet_input = {'T1': [['P1', P1, 1]], 'T2': [['P1', P1, 1]], 'T3': [['P2', P2, 1], ['P3', P3, 1]]}
    petriNet_output = {'T1': [['P2', P2, 1]], 'T2': [['P3', P3, 1]], 'T3': [['P1', P1, 1]]}
    print("Initial net:\n")
    print_net()
    x = int(input("1)Do you want the step by step display method ?\n2)Do you want to display the final solution?"))
    if find_path():
        if x == 2:
            points()
        else:
            points_verbose()
    else:
        print("Some parts of the net are isolated.\n")
        if input("Do you want to continue ? \ny/n?") == 'y':
            if x == 2:
                points()
            else:
                points_verbose()
        else:
            print("Process ended.\n")
            if input("Exit program or reset") == "reset":
                main()
                petriNet_input = {}
                petriNet_output = {}
                nodeDict = {}
    print("Final net:\n")
    print_net()
    os.system('pause')


def main():
    """Main function used to call the test function or the petriNet simulator"""
    print("What do you prefer:\n")
    x = int(input("1)Input the values manually\n2)Run the predefined test\n"))
    if x == 1:
        run_petriNet_simulator()
    else:
        test_function()


main()
