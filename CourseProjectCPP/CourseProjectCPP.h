// CourseProjectCPP.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include "entities/player.hpp"
#include "cards/cardpile.hpp"
#include "cards/basecard.hpp"
#include "cards/manaraycard.hpp"
#include "cards/barriercard.hpp"
#include "cards/magicintuitioncard.hpp"
#include "cards/fireballcard.hpp"
#include "policies/enhancedhealingpolicy.hpp"
#include "exceptions/gameruleexceptions.hpp"
#include "combat/idamagedealer.hpp"
#include "combat/itarget.hpp"

#include <exception>
#include <iostream>
#include <cstdint>
#include <memory>
#include <utility>

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.