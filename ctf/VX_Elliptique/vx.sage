# énoncé

# 𝑦² = 𝑥³ + 𝐴𝑥² + 𝑥 [𝑛]
# 𝑧 ≡ 𝑥1 [𝑛]
# 𝑧 ≡ 𝑥2 [(𝑛−1)/2]

n  = 2^255 - 19
x  = 54387532345611522562080964454373961410727797296305781726528152669705763479709
y  = 14361142164866602439359111189873751719750924094051390005776268461061669568849
y1 = 43534902453791495272426381314470202206884068238768892013952523542894895251100
y2 = 30324056046686065827439799532301040739788176334375034006985657438931650257514

# solution

F = GF(n)

E = EllipticCurve(F, [0,486662,0,1,0])

assert E.is_on_curve(x, y)

# racines de polynomes dans GF(n)
K.<x> = F[]

f1 = x^3 + 486662 * x^2 + x - y1^2
roots1 = f1.roots()

f2 = x^3 + 486662 * x^2 + x - y2^2
roots2 = f2.roots()

# théorème des restes chinois
for x1, _ in roots1:
    for x2, _ in roots2:
        # print("x1", x1)
        # print("x2", x2)

        assert E.is_on_curve(x1, y1)
        assert E.is_on_curve(x2, y2)

        z = CRT([int(x1), int(x2)], [n, (n-1)/2])
        print(z)
