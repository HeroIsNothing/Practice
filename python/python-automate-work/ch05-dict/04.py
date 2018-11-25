def addToInventory(inventory, addedItems):
    for item in addedItems:
        inventory.setdefault(item, 0)
        inventory[item] += 1
    return inventory

def displayInventory(inventory):
    print('Inventory:')
    for k, v in inventory.items():
        print(str(v).rjust(2,' '), k)

if __name__ == '__main__':
    inv = {'gold coin': 42, 'rope': 1}
    dragonLoot = ['gold coin', 'dagger', 'gold coin', 'gold coin', 'ruby']
    inv = addToInventory(inv, dragonLoot)
    displayInventory(inv)

    import sys
    sys.exit(0)