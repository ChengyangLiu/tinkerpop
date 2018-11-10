def parse(line) {
    def (id, name, age, phone, weight) = line.split(/,/).toList()
    def label = "v"
    def v1 = graph.addVertex(T.id, id, T.label, label)
    v1.property('name', name)
    v1.property('age', Integer.valueOf(age))
    v1.property('phone', age)
    v1.property('weight', Integer.valueOf(weight))
    return v1
}
