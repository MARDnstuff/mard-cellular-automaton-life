import networkx as nx
import matplotlib.pyplot as plt
import re


def createGraph(file_name):
    file = open(file_name, 'r')
    Lines = file.readlines()

    # Complete Graph
    G = nx.DiGraph()
    for line in Lines:
        par = re.split('[ \n]', line)
        par.pop(2)
        G.add_edge(par[0], par[1])
    print('G is ready')
    # Exctract attractors
    S = [G.subgraph(c).copy() for c in nx.weakly_connected_components(G)]
    print('subgraph complete')
    for i,g in enumerate(S):
        print(i)
        plt.figure(3, figsize=(20, 20))
        pos = nx.layout.random_layout(g)
        nx.draw_networkx(g, pos, node_size=50, font_size=3)
        plt.title(file_name)
        plt.savefig("new"+ str(i) + ".png")
        plt.clf()
    print("1 step completed")
    # plt.figure(3, figsize=(15, 15))
    # pos = nx.layout.spring_layout(G)
    # nx.draw_networkx(G, pos, node_size=200, font_size=8)
    # # saving
    # plt.title("3x3")
    # plt.savefig("3x3" + "new" + ".png")
    print('File saved succesfully')
    # plt.show()


if __name__ == '__main__':
    path = "/home/marco/Desktop/Basin_Attractors/Attractors/Graphic_Netwrokx_py/plotAttractor/"
    createGraph(path + input("File?: "))
