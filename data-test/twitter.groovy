def parse(line) {
    def parts = line.split(/ /)
    def (id, phone, weight) = parts[0].split(/:/).toList()
    def v1 = graph.addVertex(T.id, id)
    if (phone != null) v1.property('phone', phone)
    if (weight != null) v1.property('weight', Integer.valueOf(weight))
    if (parts.length == 2) {
        parts[1].split(/,/).grep { !it.isEmpty() }.each {
            def (refId, weight, mark) = it.split(/:/).toList()
            def v2 = graph.addVertex(T.id, refId)
            v1.addOutEdge('e', v2, 'weight', Integer.valueOf(weight), 'mark', mark)
        }
    }
    return v1
}
