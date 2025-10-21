#include <fstream>
#include "cereal/archives/json.hpp"
#include "WaffineForm.hpp"

int main() {
    // Quick I/O sanity test.
    std::ofstream file("out.json");
    cereal::JSONOutputArchive archive(file);

    WaffineForm w = WaffineForm(Winterval(-2, 3));
    w = w * WaffineForm(Winterval(4, 5)) + WaffineForm(Winterval(-1, 1));

    archive(w);
    return 0;
}