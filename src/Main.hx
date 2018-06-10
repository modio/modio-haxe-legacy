class Main 
{
    //This loads the test.ndll and 'binds' the Haxe function 'sum' to the C function 'sum'.
    //Int->Int->Int is Haxe syntax for typing a function that takes 2 integers as arguments and that returns an integer.
    static var init:Int->Int->String->Void = cpp.Lib.load("modioGlue","init",3);
    static function main()
    {
        init(1, 7, "e91c01b8882f4affeddd56c96111977b");
    }
}