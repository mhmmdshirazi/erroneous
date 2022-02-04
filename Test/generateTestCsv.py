import random
import csv


def create_random_gap_and_overlap(_node_num):
    gap_two = []
    overlap_two = []
    gap_three = []
    overlap_three = []
    for i in range(_node_num):
        gap_two.append(round(random.random() * 1000, 2))
        gap_three.append(round(random.random() * 1000, 2))
        overlap_two.append(round(random.random() * 1000, 2))
        overlap_three.append(round(random.random() * 1000, 2))
    return gap_two, overlap_two, gap_three, overlap_three


# create a table with random data
def create_data_structure_table(_sample_num, _node_num, _gap_and_overlaps):
    data_struct = [[0 for i in range(12)] for j in range(_sample_num * 2 * _node_num)]
    last_epoch = [[0 for i in range(_node_num)] for j in range(2)]
    last_duration = [[10 for i in range(_node_num)] for j in range(2)]

    gap_remained = [_gap_and_overlaps[0].copy(), _gap_and_overlaps[2].copy()]
    overlap_remained = [_gap_and_overlaps[1].copy(), _gap_and_overlaps[3].copy()]
    # Fill the first line for each node and each stream ID with epoch = 0 and duration = 10
    # The other lines will be random

    for i in range(_node_num * 2):
        data_struct[i][0] = int(i / 2)
        data_struct[i][4] = 10
        data_struct[i][7] = i % 2 + 2

    for i in range(_node_num * 2, _sample_num * 2 * _node_num):
        data_struct[i][0] = random.randint(0, _node_num - 1)
        data_struct[i][1] = 0
        data_struct[i][7] = random.randint(2, 3)
        # choose randomly between gap and overlap
        if random.randint(0, 1):
            random_gap = round(random.random(), 2) * gap_remained[data_struct[i][7] - 2][data_struct[i][0]]
            gap_remained[data_struct[i][7] - 2][data_struct[i][0]] -= random_gap
            data_struct[i][2] = last_epoch[data_struct[i][7] - 2][data_struct[i][0]] + random_gap + \
                                last_duration[data_struct[i][7] - 2][data_struct[i][0]]
            last_epoch[data_struct[i][7] - 2][data_struct[i][0]] = data_struct[i][2]
        else:
            random_overlap = round(random.random(), 2) * overlap_remained[data_struct[i][7] - 2][data_struct[i][0]]
            if random_overlap >= last_duration[data_struct[i][7] - 2][data_struct[i][0]]:
                random_overlap = last_duration[data_struct[i][7] - 2][data_struct[i][0]]
            data_struct[i][2] = last_epoch[data_struct[i][7] - 2][data_struct[i][0]] - random_overlap + \
                                last_duration[data_struct[i][7] - 2][data_struct[i][0]]
            last_epoch[data_struct[i][7] - 2][data_struct[i][0]] = data_struct[i][2]
            overlap_remained[data_struct[i][7] - 2][data_struct[i][0]] -= random_overlap
        data_struct[i][4] = round(random.random() * 100, 2)
        last_duration[data_struct[i][7] - 2][data_struct[i][0]] = data_struct[i][4]

    return data_struct, gap_remained, overlap_remained


def show_gap_and_overlaps(_gap_and_overlaps, gap_remained, overlaps_remained, node_num):
    final_gap_two = [x - y for x, y in zip(_gap_and_overlaps[0], gap_remained[0])]
    final_gap_three = [x - y for x, y in zip(_gap_and_overlaps[2], gap_remained[1])]
    final_overlap_two = [x - y for x, y in zip(_gap_and_overlaps[1], overlaps_remained[0])]
    final_overlap_three = [x - y for x, y in zip(_gap_and_overlaps[3], overlaps_remained[1])]

    for i in range(node_num):
        print('For Node {} gapTwo = {} overlapTwo = {} gapThree = {} overlapThree = {}'.format(i,
                                                                                               round(final_gap_two[i],
                                                                                                     2),
                                                                                               round(
                                                                                                   final_overlap_two[i],
                                                                                                   2),
                                                                                               round(final_gap_three[i],
                                                                                                     2), round(
                final_overlap_three[i], 2)))


if __name__ == '__main__':
    node_num = int(input('Please enter number of test nodes\n'))
    sample_num = int(input('Please enter sample number for each node\n'))
    print('This code generates random gap and overlap times for each node the range is [0,1000) seconds')
    gap_and_overlaps = create_random_gap_and_overlap(node_num)
    result = create_data_structure_table(sample_num, node_num, gap_and_overlaps)
    show_gap_and_overlaps(gap_and_overlaps, result[1], result[2], node_num)
    header = ['NodeID', 'CowID', 'Epoch', 'DetectionTime', 'Duration', 'Event', 'Source', 'StreamID', 'Latency',
              'SignalStrength', 'CloudRecieveTime', 'BatteryLevel']
    with open('testData.csv', 'w') as f:
        writer = csv.writer(f)
        writer.writerow(header)
        writer.writerows(result[0])
