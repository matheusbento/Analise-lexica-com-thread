<< "INFORME 2 NUMERO"
@X, @Y
@X 10.2
@Y 15555
>> @X >> @Y
[@X>!@Y](
    << "Numero".@X."Maior que".@Y
) [@X<@Y](
    << "Numero".@Y."Maior que".@X
)
@Z ((@X+@Y) -(10*@X))/@X
<< @Z
