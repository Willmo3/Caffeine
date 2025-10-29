#include <fstream>
#include "cereal/archives/json.hpp"
#include "AffineForm.hpp"

int main() {
    // Quick I/O sanity test.
    std::ofstream file("out.json");
    cereal::JSONOutputArchive archive(file);

    AffineForm w = AffineForm(Winterval(-2, 3));
    w = w * AffineForm(Winterval(4, 5)) + AffineForm(Winterval(-1, 1));

    archive(w);
    return 0;
}