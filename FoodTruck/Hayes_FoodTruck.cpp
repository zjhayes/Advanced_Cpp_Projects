// Food Truck Cash Register that keeps track of inventory.

// Zachary Hayes - zjhayes@dmacc.edu - August 27th, 2019

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Ingredient
{
private:
    string name;
    int currentInventory;
    int maxInventory;
    
public:
    Ingredient(string _name, int _maxInventory)
    {
        name = _name;
        currentInventory = 0; // This will be set by the user.
        maxInventory = _maxInventory;
    }
    
    // Getters and Setters
    string getName()
    {
        return name;
    }
    
    int getMaxInventory()
    {
        return maxInventory;
    }
    
    int getCurrentInventory()
    {
        return currentInventory;
    }
    void setCurrentInventory(int _currentInventory)
    {
        currentInventory = _currentInventory;
    }
    void subtractFromInventory(int _amount)
    {
        currentInventory -= _amount;
    }
    
};

class Product
{
protected:
    string name;
    float price;
    vector<Ingredient> ingredients;
    vector<int> ingredientAmount;
    bool addChilli;                     // True if chilli can be added to product.
    
public:
    Product(string _name, float _price, bool _addChilli)
    {
        name = _name;
        price = _price;
        addChilli = _addChilli;
    }
    
    Product(){}
    
    virtual ~Product(){}
    
    // Add ingredient to list of ingredients in product.
    void addIngredient(Ingredient _ingredient, int _amount)
    {
        ingredients.push_back(_ingredient);
        ingredientAmount.push_back(_amount);
    }
    
    // Getters and Setters
    virtual string getName()
    {
        return name;
    }
    virtual float getPrice()
    {
        return price;
    }
    bool getAddChilli()
    {
        return addChilli;
    }
    int getIngredientIndex(string _name)
    {
        int currentIndex = 0;
        for(auto &ingredient : ingredients)
        {
            if(ingredient.getName() == _name)
            {
                break; // Found correct index.
            }
        }
        return currentIndex;
    }
    virtual vector<Ingredient> getIngredients()
    {
        return ingredients;
    }
    int getIngredientAmount(int index)
    {
        return ingredientAmount[index];
    }
};

class ProductAddChilli : public Product
{
public:
    
    ProductAddChilli()
    {
        Product();
    }
    
    float getPrice() override
    {
        //return this.price + FoodTruck::getInstance().getAddChilliPrice();
        return NULL;
    }
    
    string getName() override
    {
        return name + " (add chilli)";
    }
    
    vector<Ingredient> getIngredients() override
    {
        // Add chilli to ingredients and return that.
        return vector<Ingredient>{};
    }
    
    void getTest()
    {
        
    }
    
};

class FoodTruck
{
private:
    
    // Set up singleton.
    static FoodTruck* instance;
    FoodTruck(){}
    
    float currency;
    vector<Ingredient*> inventory;
    vector<Product*> products;
    float addChilliPrice = 2.00;
    
    // Create ingredient objects and add them to inventory.
    void intializeIngredientInventory()
    {
        intializeInventoryItem("hamburger patty", 200); // 0
        intializeInventoryItem("hotdog", 200);          // 1
        intializeInventoryItem("hamburger bun", 75);    // 2
        intializeInventoryItem("hotdog bun", 75);       // 3
        intializeInventoryItem("chilli", 500);          // 4
        intializeInventoryItem("fry basket", 75);       // 5
        intializeInventoryItem("soda", 200);            // 6
    }
    
    void intializeInventoryItem(string _name, int _maxAmount)
    {
        Ingredient* newIngredient = new Ingredient(_name, _maxAmount);
        inventory.push_back(newIngredient);
    }
    
    // A method that isn't going to scale well and should be refactored.
    void initializeProducts()
    {
        int burgerAmounts[] = {1,0,1,0,0,0,0}; // These are like punchcards.
        initializeAProduct("Hamburger", 5.00, true, burgerAmounts);
        int hotdogAmounts[] = {0,1,0,1,0,0,0};
        initializeAProduct("Hotdog", 5.00, true, hotdogAmounts);
        int chilliAmounts[] = {0,0,0,0,12,0};
        initializeAProduct("Chilli", 4.00, false, chilliAmounts);
        int friesAmount[] = {0,0,0,0,0,1,0};
        initializeAProduct("Fries (basket)", 7.00, true, friesAmount);
        int sodaAmount[] = {0,0,0,0,0,0,1};
        initializeAProduct("Soda", 2.00, false, sodaAmount);
    }
    
    // Create a product and add to product list.
    void initializeAProduct(string _name, float _price, bool _addChilli, int ingredientAmounts[])
    {
        Product* newProduct = new Product(_name, _price, _addChilli);
        
        int ingredientIndex = 0;
        for(auto ingredient : getInventory()) // Add ingredients to product.
        {
            int ingredientAmount = ingredientAmounts[ingredientIndex];
            if(ingredientAmount > 0)
            {
                newProduct->addIngredient(*ingredient, ingredientAmount);
            }
            ingredientIndex++;
        }
        products.push_back(newProduct);
    }
    
    // Get inventory input from user and validate.
    int takeInventoryInput(Ingredient* _ingredient)
    {
        int inventoryInput;
        int maxInventory = _ingredient->getMaxInventory();
        
        cout << _ingredient->getName() << " (" << _ingredient->getMaxInventory() << "): ";
        cin >> inventoryInput;
        
        if(inventoryInput < 0 or inventoryInput > maxInventory)
        {
            cout << "Invalid input. The max inventory for this item is " << maxInventory << endl;
            cout << "Try again. ";
            inventoryInput = takeInventoryInput(_ingredient);
        }
        return inventoryInput;
    }
    
public:
    
    // Get singleton instance.
    static FoodTruck* getInstance()
    {
        if(instance == 0)
        {
            instance = new FoodTruck();
            instance->intializeIngredientInventory();
            instance->initializeProducts();
        }
        
        return instance;
    }
    
    vector<Ingredient*> getInventory()
    {
        return inventory;
    }
    
    vector<Product*> getProducts()
    {
        return products;
    }
    
    float getCurrency()
    {
        return currency;
    }
    
    float getAddChilliPrice()
    {
        return addChilliPrice;
    }
    
    int getIngredientIndex(string _name)
    {
        int currentIndex = 0;
        for(auto &ingredient : inventory)
        {
            if(ingredient->getName() == _name)
            {
                break; // Found correct index.
            }
            currentIndex++;
        }
        return currentIndex;
    }

    // Set initial inventory from user input.
    void initializeInventoryFromConsole()
    {
        cout << "Initialize Inventory" << endl;
        
        for(auto &ingredient : getInventory())
        {
            int currentInventory = takeInventoryInput(ingredient);
            ingredient->setCurrentInventory(currentInventory);
        }
    }
    
    // Use ingredients and create product.
    void makeProduct(Product _product)
    {
        for(auto ingredient : _product.getIngredients())
        {
            // Subtract from ingredients in stock.
            int inventoryIndex = getIngredientIndex(ingredient.getName());
            string ingredientName = ingredient.getName();
            int ingredientIndex = _product.getIngredientIndex(ingredientName);
            int ingredientAmount = _product.getIngredientAmount(ingredientIndex);
            inventory[inventoryIndex]->subtractFromInventory(ingredientAmount);
        }
    }
    
    // Checks list of ingredients against ingredients in stock.
    bool checkIngredients(Product * _product)
    {
        bool passed = true;
        for(auto &ingredient : _product->getIngredients())
        {
            int inventoryIndex = getIngredientIndex(ingredient.getName());
            int currentInventory = inventory[inventoryIndex]->getCurrentInventory();
            string ingredientName = ingredient.getName();
            int ingredientIndex = _product->getIngredientIndex(ingredientName);
            int ingredientAmount = _product->getIngredientAmount(ingredientIndex);
            if(ingredientAmount >= currentInventory)
            {
                cout << "Not enough " << ingredient.getName() << " in inventory." << endl;
                passed = false;
            }
        }
        
        return passed;
    }
    
    // Add money to total currency.
    void deposit(float _amount)
    {
        currency += _amount;
    }
    
};


// Constants
const int SENTINEL = 0;
const float SALES_TAX = .05;
const float LOW_INVENTORY_PERCENT = .2;


// Function Declarations
void initializeInventory();
void openRegister();
void closeRegister();
void printMenu();
void takeCustomerOrders();
bool validateOrder(int);
void askToAddChilli(Product*);
void processOrder(Product*);
float calculatePriceWithTax(float);

// Weird C++ stuff.
FoodTruck* FoodTruck::instance = 0;

int main()
{
    cout << "Rebel Food Truck" << endl << endl;
    initializeInventory();
    openRegister();
    closeRegister();
    
    return 0;
}

// Set initial inventory
void initializeInventory()
{
    FoodTruck::getInstance()->initializeInventoryFromConsole();
}

// Take and process customer orders.
void openRegister()
{
    cout << endl << "Open for business." << endl;
    printMenu();
    takeCustomerOrders();
}

// Print list of products and prices.
void printMenu()
{
    cout << endl << "------------------------------" << endl;
    cout << "            MENU" << endl;
    cout << "------------------------------" << endl << endl;
    
    int menuItem = 1;
    float addChilliPrice = FoodTruck::getInstance()->getAddChilliPrice();
    
    for(auto &product : FoodTruck::getInstance()->getProducts())
    {
        cout << std::fixed << std::setprecision(2);
        string name = product->getName();
        float price = product->getPrice();
        cout << menuItem << ". " << name << setw(20 - (int)name.length()) << "$" << price << endl;
        
        if(product->getAddChilli())
        {
            cout << "     + add chilli" << setw(6) << "$" << (price + addChilliPrice) << endl;
        }
        cout << "- - - - - - - - - - - - - - -" << endl;
        menuItem++;
    }
}

// Take customer orders until exited.
void takeCustomerOrders()
{
    cout << endl << "Place orders using menu number." << endl;
    cout << "Or enter '"<< SENTINEL << "' to close register." << endl << endl;
    
    bool exit = false;
    
    while(!exit)
    {
        int order;
        
        cout << "Order: ";
        cin >> order;
        
        exit = validateOrder(order);
    }
}

// Validate and process order. Returns true when ready to exit.
bool validateOrder(int _order)
{
    FoodTruck* truck = FoodTruck::getInstance();
    
    if(_order > 0 && _order <= truck->getProducts().size())
    {
        int orderIndex = _order - 1; // Menu number is 1 more than product index.
        Product *product = truck->getProducts()[orderIndex];
        if(product->getAddChilli())
        {
            askToAddChilli(product);
        }
        processOrder(product);
    }
    else if(_order == SENTINEL)
    {
        return true;
    }
    else
    {
        cout << "Invalid menu item. Try again." << endl;
    }
    
    return false;
}

// Processes order and outputs results.
void processOrder(Product* _product)
{
    FoodTruck* truck = FoodTruck::getInstance();
    
    if(truck->checkIngredients(_product)) // Check ingredients against stock
    {
        truck->makeProduct(*_product);
        float totalPrice = calculatePriceWithTax(_product->getPrice());
        cout << "Price: $" << totalPrice << endl << endl;
        truck->deposit(totalPrice); // Add to currency.
    }
}

float calculatePriceWithTax(float price)
{
    return price + (price * SALES_TAX);
}

void askToAddChilli(Product* _product)
{
    string answer;
    cout << "Add chilli? (y/n): ";
    cin >> answer;
    
    char answerLowerChar = tolower(answer.front(), locale());
    
    if(answerLowerChar == 'y')
    {
        ProductAddChilli productAddChilli = *new ProductAddChilli();
        *_product = productAddChilli;
        //_product->get
        
        
    }
    else if(answerLowerChar == 'n')
    {
        return;
    }
    else
    {
        cout << "Invalid entry. Try again." << endl;
        askToAddChilli(_product);
    }
}

// Output sales data.
void closeRegister()
{
    
    cout << endl << "Total earnings: $" << FoodTruck::getInstance()->getCurrency();
    cout << endl << endl;
}


