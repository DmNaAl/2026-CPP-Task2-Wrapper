#include<iostream>
#include "Engine.h"
#include "TextProcessor.h"

void test()
{
    TextProcessor tp("hello world. this is a test! is it working?");

    Wrapper replace_w(&tp, &TextProcessor::replace_words, {{"from", "world"}, {"to", "there"}});
    Wrapper find_w(&tp, &TextProcessor::find_phrase, {{"phrase", "test"}});
    Wrapper cap_words_w(&tp, &TextProcessor::capitalize_words, {});
    Wrapper cap_sent_w(&tp, &TextProcessor::capitalize_sentences, {});
    Wrapper number_w(&tp, &TextProcessor::number_sentences, {});

    Engine engine;
    engine.register_command(&replace_w, "replace");
    engine.register_command(&find_w, "find");
    engine.register_command(&cap_words_w,"capitalize_words");
    engine.register_command(&cap_sent_w, "capitalize_sentences");
    engine.register_command(&number_w, "number");

    std::cout << "=== replace (default: world -> there) ===" << std::endl << engine.execute("replace") << std::endl << std::endl;

    std::cout << "=== replace (override: hello -> goodbye) ===" << std::endl << engine.execute("replace", {{"from", "hello"}, {"to", "goodbye"}}) << std::endl << std::endl;

    std::cout << "=== find (default) ==="<< std::endl << engine.execute("find") << std::endl << std::endl;

    std::cout << "=== find (override) ===" << std::endl << engine.execute("find", {{"phrase", "nonexistent"}}) << std::endl << std::endl;

    std::cout << "=== capitalize_words ===" << std::endl << engine.execute("capitalize_words") << std::endl << std::endl;

    std::cout << "=== capitalize_sentences ===" << std::endl << engine.execute("capitalize_sentences") << std::endl << std::endl;

    std::cout << "=== number sentences ===" << std::endl << engine.execute("number") << std::endl << std::endl;
}

int main()
{
    try
    {
        test();
    }
    catch (const std::exception& e)
    {
        std::cout << "FATAL ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}