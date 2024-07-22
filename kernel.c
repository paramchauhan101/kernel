#include <stddef.h>
#include <stdint.h>

// VGA text mode buffer
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;
int vga_index = 0;

// Set VGA text mode color
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

void clear_screen() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[y * VGA_WIDTH + x] = vga_entry(' ', VGA_COLOR_BLACK);
        }
    }
    vga_index = 0;
}

void print_string(const char* str, uint8_t color) {
    while (*str) {
        if (*str == '\n') {
            vga_index += VGA_WIDTH - (vga_index % VGA_WIDTH);
        } else {
            vga_buffer[vga_index++] = vga_entry(*str, color);
        }
        str++;
    }
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

int min(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

int levenshtein(const char *s, int len_s, const char *t, int len_t) {
    int cost;

    if (len_s == 0) return len_t;
    if (len_t == 0) return len_s;

    if (s[len_s - 1] == t[len_t - 1])
        cost = 0;
    else
        cost = 1;

    return min(
        levenshtein(s, len_s - 1, t, len_t    ) + 1,
        levenshtein(s, len_s    , t, len_t - 1) + 1,
        levenshtein(s, len_s - 1, t, len_t - 1) + cost
    );
}

const char* questions[] = {
    "hi",
    "hello",
    "how are you",
    "what's your favorite book",
    "any good movie recommendations",
    "can you help me with my homework",
    "what's the latest news",
    "do you have any travel tips",
    "what's the best way to learn a new language",
    "can you explain this math problem to me",
    "what are some good restaurants nearby",
    "how do I start a new hobby",
    "what's your favorite food",
    "can you tell me a joke",
    "what are some interesting facts about space",
    "can you recommend a good book on history",
    "what are some tips for staying healthy",
    "can you help me find a recipe",
    "what's the best way to stay motivated",
    "what's the meaning of life"
};

const char* answers[] = {
    "I'm doing great, thank you! How about you?",
    "Hello! How can I assist you today?",
    "I'm just a program, but I'm here to help you!",
    "Many people enjoy classic books like 'To Kill a Mockingbird' by Harper Lee or '1984' by George Orwell.",
    "Sure! Some highly recommended movies are 'The Shawshank Redemption,' 'Inception,' 'The Godfather,' and 'Parasite.'",
    "Of course! What subject or specific problem do you need help with?",
    "I can't provide real-time news updates, but you can check reliable news sources like BBC, CNN, or Reuters for the latest news.",
    "Yes! Some travel tips include packing light, keeping your important documents safe, learning a few phrases of the local language, and researching your destination beforehand.",
    "The best way to learn a new language is to practice regularly, use language learning apps like Duolingo or Rosetta Stone, immerse yourself in the language through media, and converse with native speakers.",
    "I'd be happy to help! Please provide the specific math problem you're working on.",
    "I can't provide specific recommendations, but you can use apps like Yelp or TripAdvisor to find highly-rated restaurants near you.",
    "Start by identifying your interests, researching online for beginner guides, joining local or online communities, and setting aside regular time to practice and enjoy your new hobby.",
    "As an AI, I don't eat, but many people love pizza, sushi, pasta, and ice cream.",
    "Sure! Why don't scientists trust atoms? Because they make up everything!",
    "Here are a few: Space is completely silent; the hottest planet in our solar system is Venus, not Mercury; and there are more stars in the universe than grains of sand on all the Earth's beaches.",
    "Certainly! 'Sapiens: A Brief History of Humankind' by Yuval Noah Harari is a highly recommended read.",
    "Some tips for staying healthy include eating a balanced diet, exercising regularly, staying hydrated, getting enough sleep, and managing stress.",
    "Sure! What type of recipe are you looking for? (e.g., Italian, vegetarian, dessert, etc.)",
    "Setting clear goals, breaking tasks into manageable steps, tracking your progress, rewarding yourself for achievements, and surrounding yourself with supportive people can help you stay motivated.",
    "The meaning of life is a philosophical question that has been debated for centuries. It can vary greatly depending on individual beliefs and perspectives. Some find meaning in relationships, accomplishments, helping others, or personal growth."
};

// Define the entry point for the kernel
void kernel_start() {
    clear_screen();
    print_string("Secret OS Chatbot\n", VGA_COLOR_LIGHT_GREEN);

    // Simulating user questions
    const char* user_questions[] = {
        "hello",
        "whts your favrite book",
        "cn you help me",
        "whats your favorite food"
    };

    for (int i = 0; i < sizeof(user_questions) / sizeof(user_questions[0]); i++) {
        print_string("\nUser: ", VGA_COLOR_LIGHT_GREEN);
        print_string(user_questions[i], VGA_COLOR_LIGHT_GREEN);
        print_string("\nChatbot: ", VGA_COLOR_LIGHT_GREEN);
        find_answer(user_questions[i]);
    }

    // Halt the system
    while (1) {}
}
