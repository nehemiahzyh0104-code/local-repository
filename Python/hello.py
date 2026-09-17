from sympy import symbols, sympify, diff, pretty_print, SympifyError

while True:
    try:
        expr = input("键入表达式\t").strip()
        var = input("键入变量\t").strip()
        order = int(input("键入求导阶数\t"))

        x = symbols(var)
        fct = sympify(expr)
        
        result = diff(fct, x, order)

        print("\n导数为\t")
        pretty_print(result)
        
        go = input("继续?(y/n)")
        if go == "y":
            continue
        else:
            break

    except SympifyError:
        print("表达式错误")
    except ValueError:
        print("阶数错误")
    except Exception as e:
        print("错误：{e}")
