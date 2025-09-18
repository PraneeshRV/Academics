function compareObjects() {
    const obj1 = ['name1', 'age1', 'city1'].map(id => document.getElementById(id).value)
    const obj2 = ['name2', 'age2', 'city2'].map(id => document.getElementById(id).value)
    document.getElementById('result').textContent = obj1.every((val, i) => val === obj2[i]) 
        ? "The objects are equivalent!" 
        : "The objects are not equivalent."
}

document.getElementById('compareBtn').addEventListener('click', compareObjects)
