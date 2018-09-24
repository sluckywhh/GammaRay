/*
  problemcollector.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2018 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Anton Kreuzkamp <anton.kreuzkamp@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Own
#include "problemcollector.h"

#include "probe.h"

using namespace GammaRay;

ProblemCollector::ProblemCollector(QObject *parent)
    : QObject(parent)
{
}

ProblemCollector * ProblemCollector::instance()
{
    return Probe::instance()->problemCollector();
}

void ProblemCollector::addProblem(const Problem& problem)
{
    auto self = instance();

    if (self->m_problems.contains(problem))
        return;

    emit self->aboutToAddProblem(self->m_problems.size());
    self->m_problems.push_back(problem);
    emit self->problemAdded();
}
void ProblemCollector::removeProblem(const QString& problemId)
{
    auto self = instance();
    auto it = std::find_if(self->m_problems.begin(), self->m_problems.end(), [&](const Problem &problem) { return problem.problemId == problemId; });
    if (it == self->m_problems.end())
        return;
    auto row = std::distance(self->m_problems.begin(), it);

    emit self->aboutToRemoveProblem(row);
    self->m_problems.erase(it);
    emit self->problemRemoved();
}

const QVector<Problem> & ProblemCollector::problems()
{
    return m_problems;
}

