module hello;

import core.stdc.stdlib;
import std.stdio;

void main(string[] args)
{
    system("chcp 65001");
    if(args.length < 2)
    {
        writeln("Usage: /{app} {name}");
        return;
    }
    writefln("Olá, %s", args[1]);
    auto finput = File("test.txt", "w");
    finput.writeln("Olá, ", args[1], ", tudo bem?");
}