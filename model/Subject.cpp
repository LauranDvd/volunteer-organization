#include "Subject.h"

void Subject::notifyObservers() {
	for (const auto& observer : allObservers) {
		observer->update();
	}
}
