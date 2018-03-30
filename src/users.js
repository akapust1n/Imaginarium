import vars from './vars'
import fetchJsonp from 'fetch-jsonp'

/**
 * Вызвать метод vk api users.get для получения имен игроков
 * @param users Игроки, после выполнения у каждого игрока создается поле name
 * @param callback Функция, которая вызывается после выполнения, в параметре передаются игроки
 */
function getNames(users, callback) {
    let ids = users.map(user => user.viewer_id);
    fetchJsonp(`https://api.vk.com/method/users.get?access_token=${vars['access_token']}&v=5.73&user_ids=${ids}`)
        .then(response => response.json())
        .then(json => {
            console.log('api.vk.com/method/users.get', json);
            {
                for (let i = 0; i < users.length; i++) {
                    let user = json.response[i];
                    users[i].name = user.first_name + ' ' + user.last_name;
                }
                callback(users);
            }
        })
        .catch(ex => console.log(ex))
}

export default getNames;