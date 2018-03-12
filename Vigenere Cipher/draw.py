from matplotlib import pyplot as plt

def draw_frequecy():
    with open('frequency.dat') as f:
        title = ['plain text', 'encrypted text, n=4', 'encrypted text, n=16']
        for i in range(3):
            ca = list(map(lambda x: int(x), f.readline().rstrip().split(' ')))
            x = [chr(i+ord('a')) for i in range(26)]
            
            fig, ax = plt.subplots()
            index = range(26)
            bar_width = 0.35
            
            ax.bar(index, ca, bar_width, alpha=0.4, color='b')
            ax.set_xlabel('Letter')
            ax.set_ylabel('Frequency')
            ax.set_xticks(index)
            ax.set_xticklabels(x)
            ax.set_title(title[i])

            plt.show()

def draw_ICindex():
    with open('ICindex.dat') as f:
        ica = list(map(lambda x: float(x), f.readline().rstrip().split(' ')))
        x = [2**i for i in range(9)]
        x.insert(0, 0)

        fig, ax = plt.subplots()
        index = range(10)
        bar_width = 0.35
        
        ax.bar(index, ica, bar_width, alpha=0.4, color='g')
        ax.set_xlabel('n (n=0 means plain text)')
        ax.set_ylabel('ICindex')
        ax.set_xticks(index)
        ax.set_xticklabels(x)
        ax.set_title("ICindex for plain text and several encrypted text")

        plt.show()

if __name__ == '__main__':
    draw_ICindex()