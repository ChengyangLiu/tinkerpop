
def parse(line) {
    def (src, weight, timestamp, dst, type) = line.split(/,/).toList()
    def label = "e"
    def v1 = graph.traversal().V(Integer.valueOf(src))
    def v2 = graph.traversal().V(Integer.valueOf(dst))
    v1.addOutEdge(label, v2, 'weight', Integer.valueOf(weight), 'timestamp', timestamp)
    v2.addOutEdge(label, v1, 'weight', Integer.valueOf(weight), 'timestamp', timestamp)
    return v1
}
