import numpy
from sklearn.metrics import r2_score
from scipy import stats

# Population Data
# Age
x = [20, 22, 32, 40, 50, 36, 47]
# Income
y = [100000, 120000, 80000, 350000, 50000, 150000, 250000]
# Savings
z = [50000, 40000, 5000, 10000, 0, 30000, 8000]

# Linear regress between age and income
slope, intercept, r, p, std_err = stats.linregress(x, y)
# Linear regress between age and savings
slope1, intercept1, r1, p1, std_err1 = stats.linregress(x, z)

# List of ages for which expected income is required
values = [15, 55, 65]

# Function that calculates linear regression predicted income
def l_income(values):
    return slope * values + intercept

def l_savings(values):
    return slope1 * values + intercept1

linear_income = list(map(int, map(l_income, values)))
linear_savings = list(map(int, map(l_savings, values)))

# Calculate polynomial regression predicted Income
mymodel = numpy.poly1d(numpy.polyfit(x, y, 2))
# Calculate polynomial regression predicted Savings
mymodel1 = numpy.poly1d(numpy.polyfit(x, z, 2))

polynomial_income = list(map(int, map(mymodel, values)))
polynomial_savings = list(map(int, map(mymodel1, values)))

# Print Population Data
print("Population Data")
print("Age:", end="\t")
for age in x:
    print(age, end="\t")
print("\nIncome:", end="\t")
for income in y:
    print(income, end="\t")
print("\nSavings:", end="\t")
for saving in z:
    print(saving, end="\t")

# Print Linear and Polynomial Regression Results
print("\n(1)")
print("Linear Regression R Factors:")
print("Age vs. Income:", round(r, 3))
print("Age vs. Savings:", round(r1, 3))
print("Polynomial R^2 Factors:")
print("Age vs. Income:", round(r2_score(y, mymodel(x)), 3))
print("Age vs. Savings:", round(r2_score(z, mymodel1(x)), 3))

# Print Predicted Income and Savings
print("\nPredicted Income values by Linear and Polynomial regression for the following ages:")
print("Ages:", values)
print("Linear Regression Predicted Income:", end="\t")
for income in linear_income:
    print(income, end="\t")
print("\nPolynomial Regression Predicted Income:", end="\t")
for income in polynomial_income:
    print(income, end="\t")

print("\nPredicted Savings values by Linear and Polynomial regression for the following ages:")
print("Ages:", values)
print("Linear Regression Predicted Savings:", end="\t")
for saving in linear_savings:
    print(saving, end="\t")
print("\nPolynomial Regression Predicted Savings:", end="\t")
for saving in polynomial_savings:
    print(saving, end="\t")

# Print Percentile Calculations
print("\n(2)")
print("Calculating Income and Savings of the population by percentile calculation:")
percentiles = [25, 50, 75]
print("Population Percentile\tIncome\t\tSavings")
for percentile in percentiles:
    income_percentile = numpy.percentile(y, percentile)
    savings_percentile = numpy.percentile(z, percentile)
    print(f"{percentile}%\t\t\t{income_percentile} \t{savings_percentile}")
